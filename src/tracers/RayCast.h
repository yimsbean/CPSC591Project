#pragma once

#include "Tracer.h"

namespace Engine{
class Object;
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

		virtual Color	
		trace_ray(const Ray ray, float& tmin, const int depth) const;

		//--
		virtual Color
		trace_reflectivity(const Ray ray,const Object* obj) const;

		virtual Color	
		trace_object(const Ray ray,const Object* obj) const;

		virtual Color	
		trace_light(const Ray ray,const Object* obj) const;

		virtual Color
		trace_bubble(const Ray ray, const Object* obj) const;
};
}