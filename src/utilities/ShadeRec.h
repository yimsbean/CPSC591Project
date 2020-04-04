#pragma once

// this file contains the declaration of the class ShadeRec

#include <vector>

#include "Ray.h"
#include "Color.h"

namespace Engine{
//reference pointers
class Material;
class World;

class ShadeRec {
	public:
	
		bool				hit_an_object;		// Did the ray hit an object?
		Material* 			material_ptr;		// Pointer to the nearest object's material
		glm::vec3 			hit_point;			// World coordinates of intersection
		glm::vec3			local_hit_point;	// World coordinates of hit point on generic object (used for texture transformations)
		glm::vec3			normal;				// Normal at hit point
		Ray					ray;				// Required for specular highlights and area lights
		int					depth;				// recursion depth
		float				t;					// ray parameter
		World&				w;					// World reference
		float				u;					// texture coordinate
		float				v;					// texture coordinate
		Color            	color;
				
		ShadeRec(World& wr);					// constructor
		
		ShadeRec(const ShadeRec& sr);			// copy constructor
};

}