#pragma once
#include "Object.h"
// basic line object

namespace Engine {

class Sphere : public Object{
    public:
    //@variables

    //@basics(constructor, desturctor, ...)
        Sphere();
        Sphere(const Sphere& sp);
        Sphere(const glm::vec3& center, float radius);
        
        virtual ~Sphere();

		virtual Sphere* 
		clone() const; //allow clone

        Sphere& 														
		operator= (const Sphere& rhs);
    //@functions

        void
        set_center(const glm::vec3& c);
        void
        set_center(const double x, const double y, const double z);
        
        void
        set_radius(const double r);

        virtual void
		set_color(const Color& c);
		virtual void
		set_color(const float r, const float g, const float b);
        
        virtual bool 
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;		 					 
		
    private:
    //@variables
        glm::vec3   center;
        float       radius;
    //@basics(constructor, desturctor, ...)

    //@functions
};

inline void
Sphere::set_center(const glm::vec3& c) {
	center = c;
}
		
inline void
Sphere::set_center(const double x, const double y, const double z) {
	center.x = x;
	center.y = y;
	center.z = z;
}
		
inline void
Sphere::set_radius(const double r) {
	radius = r;
}

}