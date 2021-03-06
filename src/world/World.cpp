#include "World.h"

//#include "RayCast.h"
#include "Whitted.h"

#include "Image.h"
#include "UVSphere.h"
#include "Bubble2.h"

//for drawing
#include <mutex>

namespace Engine{

std::mutex drawmutex;

World::World(int w, int h):
	WIDTH(w),HEIGHT(h)
{initialize();}
World::~World()
{delete_world();}

void 
World::initialize(){
	//SPECIFY TRACER
	background_tracer_ptr = new RayCast(this);
	bubble_tracer_ptr = new Whitted(this,10);
	bubble_thickness = init_bubble_thickness;
	generateReflectivityTexture(); //Loader.cpp
	loadScene(1);
}
void 
World::delete_world(){
	if(ambient_ptr != nullptr)
		delete ambient_ptr;
	if(background_tracer_ptr != nullptr)
		delete background_tracer_ptr;
	if(bubble_tracer_ptr != nullptr)
		delete bubble_tracer_ptr;
}
void
World::add_bubble_thickness(float deg){
	auto degree = bubble_thickness + deg;
	if(!(degree > reflectivity_image->get_hres() && degree < 0))
	bubble_thickness = degree;
}

void
World::thickness_reset(){
	bubble_thickness = init_bubble_thickness;
}

void 
World::reset(){
	image.Destroy();
	image.Initialize();
	//camera.reset();
	lights.clear();
	objects.clear();
	bubbles.clear();
	//thickness_reset();
}

void 
World::update(){
	draw();
}

// main action done inside the loop
void 
World::draw(){
	auto t1 = std::chrono::high_resolution_clock::now();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	if(RENDER_OLD_METHOD)
		render_bubble_fresnel();
	else{
		//1. RENDER BACKGROUND
		if(!OPTIMIZED_METHOD)
			render_background();
			//image.Render();
		//2. repeat for each soap bubble
		render_bubble();
	}
	drawmutex.lock();
	image.Render();
	drawmutex.unlock();
	if(DEBUG_TIME){
		auto t2 = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
		std::cout<<"Rendering Loop Finished : "<< duration <<"ms\n";
	}
}
//--------------------------------------------------
void
World::render_background(){
	auto t1 = std::chrono::high_resolution_clock::now();

	Color		L; 								
	Ray			ray;
	ray.o = camera.get_eye();
	for (int r = 0; r < HEIGHT; r++){			// up
		for (int c = 0; c < WIDTH; c++) {		// across 		
			ray.d = camera.get_direction(glm::vec2((c-0.5*WIDTH),(r-0.5*HEIGHT)));
			//TIME CONSUMING(most time consuming(>95%))
			L = background_tracer_ptr->trace_ray(ray);
			image.SetPixel(c, r, glm::vec3(L.r,L.g,L.b));
		} 
	}
	if(DEBUG_TIME){
		auto t2 = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
		std::cout<<"\nBACKG, Background Rendering Finished : "<< duration <<"ms\n";
	}
}

//Real-time Rendering of Soap Bubbles Taking into Account Light Interference, K. Iwasaki, 2004, IEEE. [1]
void
World::render_bubble(){
	auto t1 = std::chrono::high_resolution_clock::now();
	auto t2 = std::chrono::high_resolution_clock::now();
	//REPEAT THIS STEP FOR ALL BUBBLES in descending order from viewpoint
	for(auto& bubble: bubbles){
		//some pre-calculations for speeding up
		//float radius = ((UVSphere*)bubble)->get_radius();
		//float distance = glm::distance(camera.get_eye(), bubble->get_center());
		//int MIN_X, MIN_Y, MAX_X, MAX_Y;

		Color L;
		Ray ray;
		//2-a. CREATE CUBE MAP TEXTURE
		ray.o = bubble->get_center();	//set ray centre as object centre

		float xdeg,ydeg,zdeg, PHI,THETA;
		int t_a = cube_edge_length;
		int wid=4*t_a, hei=3*t_a;
		//cube map texture
		Image* bubbleTexture = new Image(wid,hei);
				//http://paulbourke.net/miscellaneous/cubemaps/
		for (int r = 0; r < hei; r++){
			for (int c = 0; c < wid; c++) {
				float x=0,y=0;
				//-1 <= x,y <= 1
				x = 2.f*(c-0.5f*(wid-1))/(wid-1);
				y = 2.f*(r-0.5f*(hei-1))/(hei-1);
				// -PI <= THETA <= PI , -PI/2 <= PHI <= PI/2
				THETA = x * M_PI;
				PHI = y * M_PI/2.f;
				xdeg = cos(PHI) * cos(THETA);
				ydeg = sin(PHI);
				zdeg = cos(PHI) * sin(THETA);
				glm::vec3 w(xdeg,ydeg,zdeg);
				ray.d = w;
				L=background_tracer_ptr->trace_ray(ray);
				bubbleTexture->set_color(c,r,L);
				//image.SetPixel(c, r, glm::vec3(L.r,L.g,L.b));
			}
		}
		
		ImageTexture* texture_ptr = new ImageTexture;
		texture_ptr->set_image(bubbleTexture);
		
		((Bubble2*)bubble->get_material())->set_cd(texture_ptr);
		
		t2 = std::chrono::high_resolution_clock::now();
		Color R, Li;
		ray.o = camera.get_eye();
		for (int r = 0; r < HEIGHT; r++){			// up
			for (int c = 0; c < WIDTH; c++) {		// across
				ray.d = camera.get_direction(glm::vec2((c-0.5*WIDTH),(r-0.5*HEIGHT)));
		if(!OPTIMIZED_METHOD){
		//2-b. Map the reflectivity texture onto the soap bubble.
		//Render the bubble by multiplicative blending with the frame buffer
		//multiplicative => DST = DST * SRC				
				//(1 − R(λ, θ))×Lit(λ)
				//R = R(λ, θ, d)
				R = background_tracer_ptr->trace_reflectivity(ray, bubble);
				//1 - SRC_COLOR BLEND, since L_it is background
				image.MultiplicativeBlendPixel(c, r,1.f-glm::vec3(R.r,R.g,R.b));
		
		//2-c. Map the cube map textures and the texture of reflectivity to the soap bubble.
		//by using multiplicative multitexturing function.
		//Render the bubble by additive blending with the bubble rendered at step (b)
		//ADDITIVE => DST = DST + SRC
				
				//R(λ, θ)×Lir(λ)
				//cube map colour
				L = R * background_tracer_ptr->trace_object(ray, bubble);
				image.AdditiveBlendPixel(c, r, glm::vec3(L.r,L.g,L.b));
		
		//2-d. Map the light source texture to the soap bubble. 
		//Render the bubble by additive blending with the bubble rendered at step (c).
		//ADDITIVE => DST = DST + SRC
				Li = background_tracer_ptr->trace_light(ray, bubble);
				image.AdditiveBlendPixel(c, r, glm::vec3(Li.r,Li.g,Li.b));
				
		}
		else{
				L = background_tracer_ptr->trace_bubble(ray, bubble);
				image.SetPixelOnLight(c,r,glm::vec3(L.r,L.g,L.b));
		}
			} 
		}
		//WANTED OUTCOME = Lp(λ) = (1 − R(λ, θ))×Lit(λ)+R(λ, θ)×Lir(λ)
		
		//-----------
		if(false || DEBUG_CUBEMAP_TEXTURE){
			Image* img = bubbleTexture;
			int w = img->get_hres(), h = img->get_vres();
			Color cl;
			for (int r = 0; r < h; r++){
				for (int c = 0; c < w; c++) {
					cl = img->get_color(c,r);
					image.SetPixel(c, r, glm::vec3(cl.r,cl.g,cl.b));
				}
			}
		}
	}
	//wavelength texture debugging
	if(false || DEBUG_RADIANCE_TEXTURE){
		Image* img = reflectivity_image;
		int w = img->get_hres(), h = img->get_vres();
		Color cl;
		for (int r = 0; r < h; r++){
			for (int c = 0; c < w; c++) {
				cl = img->get_color(c,r);
				image.SetPixel(c, r, glm::vec3(cl.r,cl.g,cl.b));
			}
		}
	}
	if(DEBUG_TIME){
		auto t3 = std::chrono::high_resolution_clock::now();
		auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
		auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>( t3 - t2 ).count();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t3 - t1 ).count();
		std::cout<<"Bubble Texture Generation: "<< duration1 <<"ms, ";
		std::cout<<"Rendering Bubble: "<< duration2 <<"ms, ";
		std::cout<<"Bubble Rendering Finished : "<< duration <<"ms\n";
	}
}
//OLD METHOD (WHITTED< FRESNEL)
void
World::render_bubble_fresnel(){
	auto t1 = std::chrono::high_resolution_clock::now();
	Color L;
	Ray ray;
	int depth = 0;
	depth = 0;
	ray.o = camera.get_eye();
	for (int r = 0; r < HEIGHT; r++){			// up
		for (int c = 0; c < WIDTH; c++) {		// across 
			ray.d = camera.get_direction(glm::vec2((c-0.5*WIDTH),(r-0.5*HEIGHT)));
			//TIME CONSUMING(most time consuming(>95%))
			L = bubble_tracer_ptr->trace_ray(ray,depth);
			image.SetPixel(c, r, glm::vec3(L.r,L.g,L.b));
		} 
	}
	
	//----------
	if(DEBUG_TIME){
		auto t2 = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
		std::cout<<"Fresnel Bubble Rendering Finished : "<< duration <<"ms\n";
	}
}
//--------------------------------------------------
//OLD METHOD, CALLBACK FUNCTION (Whitted, all objects)
ShadeRec									
World::hit_objects(const Ray& ray) {
	ShadeRec	sr(*this); 
	double		t;
	glm::vec3	normal;
	glm::vec3 	local_hit_point;
	float		tmin 			= std::numeric_limits<float>::max();
	std::vector<Object*> allobjs = bubbles;
	allobjs.insert( allobjs.end(), objects.begin(), objects.end() );
	
	for (auto obj : allobjs){
		if (obj->hit(ray, t, sr) && (t < tmin)) {
			sr.hit_an_object	= true;
			tmin 				= t;
			sr.material_ptr     = obj->get_material();
			sr.hit_point 		= ray.o + (float)t * ray.d;
			normal 				= sr.normal;
			local_hit_point	 	= sr.local_hit_point;
		}
	}
  
	if(sr.hit_an_object) {
		sr.t = tmin;
		sr.normal = normal;
		sr.local_hit_point = local_hit_point;
	}
	return(sr);   
}
//--------------------------------------------------
//CALLBACK FUNCTION (Raycast)
//for each object hit/nohit
ShadeRec									
World::hit_background_objects(const Ray& ray) {
	ShadeRec	sr(*this); 
	double		t;
	glm::vec3	normal;
	glm::vec3 	local_hit_point;
	float		tmin 			= std::numeric_limits<float>::max();

	for (auto& obj : objects){
		//not so efficient though
		if (obj->hit(ray, t, sr) && (t < tmin)) {
			sr.hit_an_object	= true;
			tmin 				= t;
			sr.material_ptr     = obj->get_material();
			sr.hit_point 		= ray.o + (float)t * ray.d;
			normal 				= sr.normal;
			local_hit_point	 	= sr.local_hit_point;
		}
	}
  
	if(sr.hit_an_object) {
		sr.t = tmin;
		sr.normal = normal;
		sr.local_hit_point = local_hit_point;
	}
	return(sr);   
}
//CALLBACK FUNCTION (Raycast, single object, without light)
ShadeRec
World::hit_object(const Ray& ray,const Object* obj){
	ShadeRec	sr(*this); 
	double		t;
	glm::vec3	normal;
	glm::vec3 	local_hit_point;
	float		tmin 			= std::numeric_limits<float>::max();

	if (obj->hit(ray, t, sr) && (t < tmin)) {
		sr.hit_an_object	= true;
		tmin 				= t;
		sr.material_ptr     = obj->get_material();
		sr.hit_point 		= ray.o + (float)t * ray.d;
		normal 				= sr.normal;
		local_hit_point	 	= sr.local_hit_point;
		//anything closer than bubble?
		
		for (auto bobj : objects){
			if(bobj->hit(ray, t, sr) && (t < tmin)){
				sr.hit_an_object = false;
				return(sr);
			}
		}
		
	}
	if(sr.hit_an_object) {
		sr.t = tmin;
		sr.normal = normal;
		sr.local_hit_point = local_hit_point;
	}
	return(sr); 		
}

}
