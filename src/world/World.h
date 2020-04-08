#pragma once

// std
#include <vector>
#include <iostream>
#include <chrono>

#include <limits>

#include "Constants.h"

//#include "Tracer.h"
#include "RayCast.h"
#include "Whitted.h"

//basic elements
#include "Color.h"
#include "Light.h"
#include "Ambient.h"
#include "PointLight.h"
#include "Object.h"

#include "Material.h"

#include "Camera.h"
#include "Ray.h"

#include "Image.h"
//for functions
#include "Imagebuffer.h"


namespace Engine{
class Object; //pointer

class World {
public:
    int currentScene = 1;
    Color				background_color = black;

    ImageBuffer         image;
    Camera              camera;
    Light*   		    ambient_ptr = nullptr;
    RayCast*			background_tracer_ptr = nullptr;
    Whitted*			bubble_tracer_ptr = nullptr;

    std::vector<Light*> lights;
    std::vector<Object*> objects;

    std::vector<Object*> bubbles;
    //int texture_a = 120;
    //std::vector<Image*> bubbleTextures;
    
    World(int w, int h);
    virtual ~World();

    int WIDTH;   //640   //768
    int HEIGHT;  //360   //432

    //updating variables(= reload)
    void
    update();
    //painting to window
    void 
    draw();

    void
    render_background();

    void
    render_bubble();

    //old method(fresnel + whitted)
    void
    render_bubble_fresnel();

    void
    initialize();
    void 
    delete_world();

    void
    loadScene(int sceneNo);

    ShadeRec
	hit_background_objects(const Ray& ray);

    ShadeRec
	hit_objects(const Ray& ray);

    ShadeRec
	hit_object(const Ray& ray,const Object* obj);

    ShadeRec
	hit_light(const Ray& ray,const Object* obj);
    
private:
    
    void
    scene1();

    void
    scene2();

    void
    readFromSceneFile(const char*);

    void
    reset();
};

}
