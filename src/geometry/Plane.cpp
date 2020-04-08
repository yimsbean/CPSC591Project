#include "Plane.h"
#include "Object.h"

namespace Engine{
//#Plane =========
//public------
//@basics(constructor, desturctor, ...)

//constructor
Plane::Plane():
	Object(),
	point(glm::vec3(0.f)),
	normal(glm::vec3(0.f,1.f,0.f))
{}
Plane::Plane(const Plane& pl):
	Object(),
	point(pl.point),
	normal(pl.normal)
{}
Plane::Plane (const glm::vec3& point, const glm::vec3& normal):
	Object(),
	point(point),
	normal(glm::normalize(normal))
{}

Plane::~Plane() 
{}

Plane* 
Plane::clone () const {
	return (new Plane (*this));
}

Plane& 
Plane::operator= (const Plane& rhs) {
	if (this == &rhs) return (*this);
    Object::operator=(rhs); point=rhs.point; normal=rhs.normal;
	return (*this);
}


//@functions
// Hit function
void
Plane::set_color(const Color& c){
	color = c;
}
void
Plane::set_color(const float r, const float g, const float b){
	color = Color(r,g,b);
}
bool
Plane::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	float t = glm::dot((point - ray.o),normal) / glm::dot(ray.d,normal); 
														
	if (t > EPSILON) {
		tmin = t;
		sr.normal = normal;
		sr.local_hit_point = ray.o + t * ray.d;
		
		return (true);	
	}

	return(false);
}

// Hit function for shadow rays
glm::vec3
Plane::get_center(){
	return point;
}

//private------
//@basics(constructor, desturctor, ...)
//@functions

}