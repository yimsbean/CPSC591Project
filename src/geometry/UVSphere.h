#pragma once
#include "Object.h"
// basic line object

namespace Engine {

class UVSphere : public Object{
    public:
    //@variables

    //@basics(constructor, desturctor, ...)
        UVSphere();
        UVSphere(const UVSphere& sp);
        UVSphere(const glm::vec3& center, float radius);
        
        virtual ~UVSphere();

		virtual UVSphere* 
		clone() const; //allow clone

        UVSphere& 														
		operator= (const UVSphere& rhs);
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
		
        virtual glm::vec3
		get_center();

        float
        get_radius();
    private:
    //@variables
        glm::vec3   center;
        float       radius;
    //@basics(constructor, desturctor, ...)

    //@functions
};

inline void
UVSphere::set_center(const glm::vec3& c) {
	center = c;
}
		
inline void
UVSphere::set_center(const double x, const double y, const double z) {
	center.x = x;
	center.y = y;
	center.z = z;
}
		
inline void
UVSphere::set_radius(const double r) {
	radius = r;
}
inline float
UVSphere::get_radius(){
    return radius;
}
}