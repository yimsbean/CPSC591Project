#pragma once

#include "Constants.h"

#include "Color.h"
#include "Material.h"
#include "ShadeRec.h"
#include "Ray.h"

namespace Engine{

class Object {
    public:
    //@variables

    //@basics(constructor, desturctor, ...)
        Object();
        Object (const Object& object);
        virtual ~Object();

		virtual Object* 
		clone() const = 0;

    //@functions
        virtual bool
		hit(const Ray& ray, double& t, ShadeRec& s) const = 0;

		bool
		shadow_hit(const Ray& ray, double& t);

		
		virtual void 							// This needs to be virtual so that it can be overridden in Compound
		set_material(Material* mPtr); 			// It therefore shouldn't be inlined
		
		Material*					
		get_material() const;

				   
		// The following three functions are only required for Chapter 3
		
		virtual void
		set_color(const Color& c);
        
		virtual void
		set_color(const float r, const float g, const float b);
		
		Color
		get_color();

		virtual glm::vec3
		get_center();
    protected:
    //@variables
        // mutable allows the const functions Compound::hit, Instance::hit, and RegularGrid::hit to assign to material_ptr
        mutable Material*   material_ptr = nullptr;
        // only used for Bare Bones ray tracing
		Color   			color;

        // Texture texture;

	//@basics(constructor, desturctor, ...)
		Object&						
		operator= (const Object& rhs);
    //@functions

};

}