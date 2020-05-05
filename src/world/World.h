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

//for functions
#include "Image.h"
#include "Imagebuffer.h"


namespace Engine{
    //pointers
class Object;
class ImageTexture;

class World {
public:
    int currentScene = 1;
    Color				background_color = black;

    ImageBuffer         image;
    Camera              camera;
    Light*   		    ambient_ptr = nullptr;
    Whitted*			bubble_tracer_ptr = nullptr;    //for OLD METHOD

    RayCast*			background_tracer_ptr = nullptr;
    Image*              reflectivity_image = nullptr;

    std::vector<Light*> lights;
    std::vector<Object*> objects;

    std::vector<Object*> bubbles;

    int cube_edge_length = 60;	//each length of cube edge
    float init_bubble_thickness = 23;
    float bubble_thickness; //0~2000nm,*10nm,
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
    
    void
    add_bubble_thickness(float degree);

    void
    thickness_reset();
    
    void
    generateReflectivityTexture();
    
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
