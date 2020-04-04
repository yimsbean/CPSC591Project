#pragma once

#include "Tracer.h"
namespace Engine{
class RayCast: public Tracer {
	public:
		
		RayCast(void);
		
		RayCast(World* _worldPtr);
				
		virtual											
		~RayCast(void);		

		virtual Color	
		trace_ray(const Ray& ray) const;

		virtual Color	
		trace_ray(const Ray ray, const int depth) const;
};
}