#pragma once
// composite object
#include "Object.h"

#include <vector>
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"

namespace Engine {

class Composite : public Object{
    public:
    //@variables

    //@basics(constructor, desturctor, ...)
        Composite();
        Composite(const Composite& comp);
        Composite(const std::vector<Object*> objects);

        virtual ~Composite();

		virtual Composite* 
		clone() const;  //allow clone

        Composite& 														
		operator= (const Composite& rhs);
    //@functions
        virtual void
		set_color(const Color& c);
		virtual void
		set_color(const float r, const float g, const float b);

        virtual bool 
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;		 					 
		
    private:
    //@variables
        std::vector<Object*> objects;
    //@basics(constructor, desturctor, ...)

    //@functions
        void delete_objects();
};

}