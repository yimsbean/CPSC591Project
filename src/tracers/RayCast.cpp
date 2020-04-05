#include "RayCast.h"
#include "World.h"
#include "ShadeRec.h"
#include "Material.h"
#include <iostream>
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
	ShadeRec sr(world_ptr->hit_objects(ray));
		
	if (sr.hit_an_object) {
		sr.ray = ray;			// used for specular shading
		return (sr.material_ptr->shade(sr));
	}   
	else{
		return (world_ptr->background_color);
	}
}


// -------------------------------------------------------------------- trace_ray
// this ignores the depth argument

Color	
RayCast::trace_ray(const Ray ray, const int depth) const {
	ShadeRec sr(world_ptr->hit_objects(ray));
		
	if (sr.hit_an_object) {
		sr.ray = ray;			// used for specular shading
		return (sr.material_ptr->shade(sr));
	}   
	else{
		return (world_ptr->background_color);
	}
}

Color
RayCast::trace_ray(const Ray ray, float& tmin, const int depth) const{
	return trace_ray(ray,depth);
}


}