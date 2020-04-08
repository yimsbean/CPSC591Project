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


#include "json.hpp"

namespace Engine{

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
				}	
				else if(elm["type"] == "bubble2"){
					auto pt = elm["geometry"];
					UVSphere* obj= new UVSphere(
						glm::vec3(pt[0].get<float>(),pt[1].get<float>(),pt[2].get<float>()),
						pt[3].get<float>(),
						camera.get_eye()
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
    std::cout<<"Scene objects loaded\n";
}
}