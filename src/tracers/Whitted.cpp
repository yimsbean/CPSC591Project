// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Whitted.h"
#include "World.h"
#include "ShadeRec.h"
#include "Material.h"
namespace Engine{
// -------------------------------------------------------------------- default constructor

Whitted::Whitted(int maxDepth)
	: Tracer(), maxDepth(maxDepth)
{}


// -------------------------------------------------------------------- constructor
		
Whitted::Whitted(World* _worldPtr,int maxDepth)
	: Tracer(_worldPtr), maxDepth(maxDepth)
{}


// -------------------------------------------------------------------- destructor

Whitted::~Whitted(void) {}


// -------------------------------------------------------------------- trace_ray

Color	
Whitted::trace_ray(const Ray ray, const int depth) const {
	if (depth > maxDepth){
		return(black);
	}
	else {
		ShadeRec sr(world_ptr->hit_objects(ray));    
					
		if (sr.hit_an_object) {
			sr.depth = depth;
			sr.ray = ray;	
			return (sr.material_ptr->shade(sr));   
		}
		else
			return (world_ptr->background_color);
	}																																			
}

Color	
Whitted::trace_ray(const Ray ray, float& tmin, const int depth) const {
	if (depth > maxDepth){
		return(black);
	}
	else {
		ShadeRec sr(world_ptr->hit_objects(ray));    
					
		if (sr.hit_an_object) {
			sr.depth = depth;
			sr.ray = ray;	
			tmin		= sr.t;     // required for colored transparency 
			return (sr.material_ptr->shade(sr));   
		}
		else
			tmin = std::numeric_limits<float>::max();
			return (world_ptr->background_color);
	}																																			
}
}