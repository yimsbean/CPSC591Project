#include "RayCast.h"
#include "World.h"
#include "ShadeRec.h"
#include "Material.h"
#include <iostream>

#include <Bubble2.h>
namespace Engine{
// -------------------------------------------------------------------- default constructor

RayCast::RayCast(void)
	: Tracer()
{}


// -------------------------------------------------------------------- constructor
		
RayCast::RayCast(World* _worldPtr)
	: Tracer(_worldPtr)
{}


// -------------------------------------------------------------------- destructor

RayCast::~RayCast(void) {}


// -------------------------------------------------------------------- trace_ray

Color	
RayCast::trace_ray(const Ray& ray) const {
	ShadeRec sr(world_ptr->hit_background_objects(ray));
		
	if (sr.hit_an_object) {
		sr.ray = ray;			// used for specular shading
		return (sr.material_ptr->shade(sr));
	}   
	else{
		return (world_ptr->background_color);
	}
}
Color	
RayCast::trace_ray(const Ray ray, const int depth) const {
	return trace_ray(ray);
}
Color
RayCast::trace_ray(const Ray ray, float& tmin, const int depth) const{
	return trace_ray(ray,depth);
}
//-----
//2-b
Color
RayCast::trace_reflectivity(const Ray ray,const Object* obj) const{
	ShadeRec sr(world_ptr->hit_object(ray,obj));
	if (sr.hit_an_object) {
		sr.ray = ray;
		return (((Bubble2*)(sr.material_ptr))->reflectivityShade(sr));
	}   
	else{
		//no colour added
		return (black);
	}
}
//2-c
Color	
RayCast::trace_object(const Ray ray, const Object* obj) const{
	ShadeRec sr(world_ptr->hit_object(ray,obj));
	if (sr.hit_an_object) {
		sr.ray = ray;
		return (((Bubble2*)(sr.material_ptr))->textureShade(sr));
	}  
	else{
		//no colour added
		return (black);
	}
}
//2-d
Color	
RayCast::trace_light(const Ray ray, const Object* obj) const{
	ShadeRec sr(world_ptr->hit_object(ray,obj));
	if (sr.hit_an_object) {
		sr.ray = ray;			// used for specular shading
		return (((Bubble2*)(sr.material_ptr))->lighting(sr));
	}
	else{
		//no colour added
		return (black);
	}
}
//sum of all
Color
RayCast::trace_bubble(const Ray ray, const Object* obj) const{
	ShadeRec sr(world_ptr->hit_object(ray,obj));
	if (sr.hit_an_object) {
		sr.ray = ray;			// used for specular shading
		return (((Bubble2*)(sr.material_ptr))->shade_bubble(sr,trace_ray(ray)));
	}   
	else{
		return trace_ray(ray);
	}
}

}