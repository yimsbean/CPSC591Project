#include "World.h"

//#include "RayCast.h"
#include "Whitted.h"

#include "Triangle.h"
#include "Sphere.h"
#include "Plane.h"
#include "Composite.h"

#include "Matte.h"
#include "Phong.h"
#include "Reflective.h"
#include "Bubble.h"	//CORE MATERIAL!


#include <fstream>
#include <sstream>
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
	tracer_ptr = new Whitted(this,10);
	loadScene(1);
}
void 
World::delete_world(){
	if(ambient_ptr != nullptr)
		delete ambient_ptr;
	if(tracer_ptr != nullptr)
		delete tracer_ptr;
}

void 
World::update(){
	draw();
}

// main action done inside the loop
void 
World::draw(){
	drawmutex.lock();
	auto t1 = std::chrono::high_resolution_clock::now();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	Color		L; 								
	Ray			ray;
	int 		depth = 0;

	ray.o = camera.get_eye();
	for (int r = 0; r < HEIGHT; r++){			// up
		for (int c = 0; c < WIDTH; c++) {		// across 					
			L = black; 
			ray.d = camera.get_direction(glm::vec2((c-0.5*WIDTH),(r-0.5*HEIGHT)));
			//TIME CONSUMING(most time consuming(>95%))
			L += tracer_ptr->trace_ray(ray, depth);

			if(DEBUG_RENDER_COLOR){
				if(L.r > 1.0f || L.g > 1.0f || L.b > 1.0f)
					std::cout<<"("<<r<<", "<<c<<"), ["<<L.r<<", "<<L.g<<", "<<L.b <<"]\n";
			}
			image.SetPixel(c, r, glm::vec3(L.r,L.g,L.b));
		} 
	}
	image.Render();
	if(DEBUG_TIME){
		auto t2 = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();
		std::cout<<"Drawing Finished : "<< duration <<"ms\n";
	}
	drawmutex.unlock();
}
void World::reset(){
	image.Destroy();
	image.Initialize();
	camera.reset();
	lights.clear();
	objects.clear();
}

//for each object hit/nohit
ShadeRec									
World::hit_objects(const Ray& ray) {
	ShadeRec	sr(*this); 
	double		t;
	glm::vec3	normal;
	glm::vec3 	local_hit_point;
	float		tmin 			= std::numeric_limits<float>::max();
	//int 		num_objects 	= objects.size();
	for (auto obj : objects){
	//for (int j = 0; j < num_objects; j++)
		//if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
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
void
World::readFromSceneFile(const char* fileName){
	//0. AMBIENT LIGHT
    Ambient* amb_ptr = new Ambient;
	amb_ptr->scale_radiance(0.5);
	ambient_ptr = amb_ptr;
	//1. BACKGROUND COLOUR
	background_color = Color(0.1f,0.1f,0.1f);

	//2. LOAD FROM FILE(json)
    std::ifstream i(fileName);
    if(i.fail()){ std::cerr<<"ERROR IN READING JSON FILE\n";exit(1);}
    nlohmann::json j;
    i >> j;
	if(j.empty()) return;
	std::string temp;
    for (auto& element : j.items()) {
		//LOAD CAMERA
		if(element.key() == "camera"){
			//__comment, eye, lookat, up, fov
			auto elm = element.value();
			camera.set_eye(elm["eye"][0].get<float>(),elm["eye"][1].get<float>(),elm["eye"][2].get<float>());
			camera.set_lookat(elm["lookat"][0].get<float>(),elm["lookat"][1].get<float>(),elm["lookat"][2].get<float>());
			camera.set_up(elm["up"][0].get<float>(),elm["up"][1].get<float>(),elm["up"][2].get<float>());
			camera.set_fov(elm["fov"].get<float>());
		}
		//LOAD LIGHTS
		else if(element.key() == "lights"){
			//__comment, type, geometry, strength
			for(auto& elm : element.value()){
				if(elm["type"] == "point"){
					auto pt = elm["geometry"];
					PointLight* light_ptr1 = new PointLight;
					light_ptr1->set_location(
						glm::vec3(pt[0].get<float>(),pt[1].get<float>(),pt[2].get<float>())
					);
					light_ptr1->scale_radiance(elm["strength"].get<float>());
					lights.push_back(light_ptr1);
				}
			}
		}
		//LOAD OBJECTS
		else if(element.key() == "objects"){
			//__comment, type, geometry, color, material
			for(auto& elm : element.value()){
				if(elm["type"] == "triangle"){
					auto pt = elm["geometry"];
					Triangle* obj= new Triangle(
						glm::vec3(pt[0].get<float>(),pt[1].get<float>(),pt[2].get<float>()),
						glm::vec3(pt[3].get<float>(),pt[4].get<float>(),pt[5].get<float>()),
						glm::vec3(pt[6].get<float>(),pt[7].get<float>(),pt[8].get<float>())
					);
					Color color = Color((int)std::stoul(elm["color"].get<std::string>(), nullptr, 16));
					//obj->set_color(color);
					Material* mat;
					if(elm["material"] == "reflective"){
						Reflective* matte = new Reflective();
						matte->set_ka(0.25); 
						matte->set_kd(0.5);
						matte->set_cd(color);
						//matte->set_ks(0.15);
						//matte->set_exp(100.0);
						matte->set_kr(0.75);
						matte->set_cr(color);
						mat = matte;
					}
					else{
						Matte* matte = new Matte();
						matte->set_cd(color);
						matte->set_kd(0.5f);
						mat = matte;
					}
					obj->set_material(mat);
					objects.push_back(obj);
				}
				else if(elm["type"] == "sphere"){
					auto pt = elm["geometry"];
					Sphere* obj= new Sphere(
						glm::vec3(pt[0].get<float>(),pt[1].get<float>(),pt[2].get<float>()),
						pt[3].get<float>()
					);
					Color color = Color((int)std::stoul(elm["color"].get<std::string>(), nullptr, 16));
					//obj->set_color(color);
					Material* mat;
					if(elm["material"] == "bubble"){
						Bubble* matte = new Bubble();
						/*
						matte->set_ka(0.25); 
						matte->set_kd(0.5);
						matte->set_cd(color);
						matte->set_kr(0.75);
						matte->set_cr(color);
						*/
						matte->set_eta_in(1.5);
						matte->set_eta_out(1.0);
						matte->set_cf_in(white);
						matte->set_cf_out(Color((int)0xEEEEEEEE));
						mat = matte;
					}
					else if(elm["material"] == "reflective"){
						Reflective* matte = new Reflective();
						matte->set_ka(0.25); 
						matte->set_kd(0.5);
						matte->set_cd(color);
						//matte->set_ks(0.15);
						//matte->set_exp(100.0);
						matte->set_kr(0.75);
						matte->set_cr(color);
						mat = matte;
					}
					else{
						Matte* matte = new Matte();
						matte->set_cd(color);
						matte->set_kd(0.5f);
						mat = matte;
					}
					obj->set_material(mat);
					objects.push_back(obj);

				}
				else if(elm["type"] == "plane"){
					auto pt = elm["geometry"];
					Plane* obj= new Plane(
						glm::vec3(pt[0].get<float>(),pt[1].get<float>(),pt[2].get<float>()),
						glm::vec3(pt[3].get<float>(),pt[4].get<float>(),pt[5].get<float>())
					);
					Color color = Color((int)std::stoul(elm["color"].get<std::string>(), nullptr, 16));
					//obj->set_color(color);
					Material* mat;
					if(elm["material"] == "reflective"){
						Reflective* matte = new Reflective();
						matte->set_ka(0.25); 
						matte->set_kd(0.5);
						matte->set_cd(color);
						//matte->set_ks(0.15);
						//matte->set_exp(100.0);
						matte->set_kr(0.75);
						matte->set_cr(color);
						mat = matte;
					}
					else{
						Matte* matte = new Matte();
						matte->set_cd(color);
						matte->set_kd(0.5f);
						mat = matte;
					}
					obj->set_material(mat);
					objects.push_back(obj);
				}
			}	
		}
    }
    std::cout<<"Scene objects loaded\n";
}
}
