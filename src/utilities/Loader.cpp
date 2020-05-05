#include "World.h"

#include <fstream>
#include <sstream>

#include "Triangle.h"
#include "Sphere.h"
#include "Plane.h"
#include "Composite.h"
#include "UVSphere.h"

#include "Matte.h"
#include "Phong.h"
#include "Reflective.h"
#include "Bubble.h"	//CORE MATERIAL!
#include "Bubble2.h"


#include "specrend.h"
#include "json.hpp"

namespace Engine{
//R(λ, θ, d)
float
get_cos_lambda_theta(float lambda, float theta, float d){
	float cos_lambda_theta,r_lambda_theta;
	float r_parallel,r_perpendicular,cos_theta_i,cos_theta_t;
	float eta = 1.33;

	cos_theta_i = glm::cos(theta);
	cos_theta_t = sqrt (1.0 - (1.0 - cos_theta_i * cos_theta_i) / (eta * eta));
	r_parallel 		= (eta * cos_theta_i - cos_theta_t) / (eta * cos_theta_i + cos_theta_t);
	r_perpendicular = (cos_theta_i - eta * cos_theta_t) / (cos_theta_i + eta * cos_theta_t);

	cos_lambda_theta = 4*M_PI/lambda*eta*d*cos_theta_i;
	return pow(r_parallel,2)*(1-cos_lambda_theta)/(1+pow(r_parallel,4)-2*pow(r_parallel,2)*cos_lambda_theta) +
		pow(r_perpendicular,2)*(1-cos_lambda_theta)/(1+pow(r_perpendicular,4)-2*pow(r_perpendicular,2)*cos_lambda_theta);
			
}
void
World::generateReflectivityTexture(){
	//x = 0~2000nm, each 10nm
	//y = 0~90(degree), each 1deg
	Color L;
	int wid = 201, hei = 91;
	int dx = 10, dy = 1;
	float ddx,ddy;

	//http://www.fourmilab.ch/documents/specrend
	double x,y,z,r,g,b;
	struct colourSystem *cs = &SMPTEsystem;
	
	//https://en.wikipedia.org/wiki/Sodium-vapor_lamp
	//double bbtemp = 2700; //2600K~2800K for the sodium lamp
	double sodium_light_wavelength = 589;	//589 nm
	//https://www.photonics.com/Articles/Light-Emitting_Diodes_A_Primer/a36706
	double blue_led_light_wavelength = 475;		//450~475nm
	double green_led_light_wavelength = 525;	//520~530nm
	double yellow_led_light_wavelength = 590;	//590nm
	double red_led_light_wavelength = 625;		//625nm
	double limegreen_led_light_wavelength = 656;	//656nm
	double orange_led_light_wavelength = 605;	//605nm
	
	double lights[]={
		sodium_light_wavelength,
		blue_led_light_wavelength,
		green_led_light_wavelength,
		red_led_light_wavelength
	};
	std::cout<<LIGHT_TEXTURE_METHOD<<"@\n";
	double light_wavelength = lights[LIGHT_TEXTURE_METHOD];

	Image* texture = new Image(wid,hei);
	for(int j=0;j<hei;++j){
		for(int i=0;i<wid;++i){
			//R(λ, θ, d)E(λ), x = d, y = θ
			ddx = dx * i;			// x = d
			ddy = glm::radians((float)dy * j);	// y = θ
			
			spectrum_to_xyz(light_wavelength,&x, &y, &z);
       		xyz_to_rgb(cs, x, y, z, &r, &g, &b);
			L = Color(r,g,b)*get_cos_lambda_theta(light_wavelength,ddy,ddx);

			//image.SetPixel(i, j, glm::vec3(L.r,L.g,L.b));
			texture->set_color(i,j,L);
		}
	}
	reflectivity_image = texture;
	//image.Render();
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
			camera.recalcUVW();
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
				else if(elm["type"] == "bubble"){
					if(RENDER_OLD_METHOD){
						auto pt = elm["geometry"];
						Sphere* obj= new Sphere(
							glm::vec3(pt[0].get<float>(),pt[1].get<float>(),pt[2].get<float>()),
							pt[3].get<float>()
						);

						Color color = Color((int)std::stoul(elm["color"].get<std::string>(), nullptr, 16));
						//obj->set_color(color);
						Material* mat;
						
						Bubble* matte = new Bubble();
						//Water(bubble) Refraction coefficient = 1.33
						matte->set_eta(1/1.03);
						matte->set_cf(white);
						mat = matte;
						
						obj->set_material(mat);
						bubbles.push_back(obj);
					}else{
						auto pt = elm["geometry"];
						UVSphere* obj= new UVSphere(
							glm::vec3(pt[0].get<float>(),pt[1].get<float>(),pt[2].get<float>()),
							pt[3].get<float>()
						);
						Color color = Color((int)std::stoul(elm["color"].get<std::string>(), nullptr, 16));
						//obj->set_color(color);
						Material* mat;
						Bubble2* matte = new Bubble2();					
						//set cd(texture) later
						mat = matte;
						obj->set_material(mat);
						bubbles.push_back(obj);
					}
				}
			}
		}
    }
    std::cout<<"Scene objects loaded\n";
}
}