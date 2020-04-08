#pragma once
#include "Object.h"
// basic line object

namespace Engine {

class Plane : public Object{
    public:
    //@variables

    //@basics(constructor, desturctor, ...)
        Plane();
        Plane(const Plane& pl);
        Plane(const glm::vec3& point, const glm::vec3& normal);
        virtual ~Plane();

		virtual Plane* 
		clone() const; //allow clone

        Plane& 														
		operator= (const Plane& rhs);
    //@functions


        virtual void
		set_color(const Color& c);
		virtual void
		set_color(const float r, const float g, const float b);
        
        virtual bool 
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;		 					 
		
        virtual glm::vec3
		get_center();
    private:
    //@variables
        glm::vec3   point;
        glm::vec3   normal;
    //@basics(constructor, desturctor, ...)

    //@functions

};

}