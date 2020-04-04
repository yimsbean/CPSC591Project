#pragma once

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Constants.h"
#include "Ray.h"
#include "Color.h"

namespace Engine{
	
class World;

class Tracer {
	public:
	
		Tracer(void);									
		
		Tracer(World* _world_ptr);						
				
		virtual											
		~Tracer(void);									

		virtual Color			// only overridden in the tracers SingleSphere and MultipleObjects
		trace_ray(const Ray& ray) const;

		virtual Color	
		trace_ray(const Ray ray, const int depth) const;
				
	protected:
	
		World* world_ptr;
};
}
