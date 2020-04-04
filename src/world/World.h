#pragma once

// std
#include <vector>
#include <iostream>
#include <chrono>

#include <limits>

#include "Constants.h"

//basic elements
#include "Color.h"
#include "Light.h"
#include "Ambient.h"
#include "PointLight.h"
#include "Object.h"

#include "Material.h"

#include "Camera.h"
#include "Ray.h"
#include "RayCast.h"
#include "Tracer.h"
#include "ViewPlane.h"

//for functions
#include "Imagebuffer.h"
#include "json.hpp"


namespace Engine{
class Object; //pointer

class World {
public:
    int currentScene = 1;
    ViewPlane			vp;
    Color				background_color = black;

    ImageBuffer         image;
    Camera              camera;
    Light*   		    ambient_ptr = nullptr;
    Tracer*				tracer_ptr = nullptr;

    std::vector<Light*> lights;
    std::vector<Object*> objects;

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
    initialize();
    void 
    delete_world();

    void
    loadScene(int sceneNo);

    ShadeRec
	hit_objects(const Ray& ray);
    
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
