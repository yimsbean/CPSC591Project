#include "Sphere.h"
#include "Object.h"
						
namespace Engine{
//#Sphere =========
//public------
//@basics(constructor, desturctor, ...)

//constructor
Sphere::Sphere():
	Object(),
	center(glm::vec3(0.f)),
	radius(1.f)
{}
Sphere::Sphere(const Sphere& sp):
	Object(),
	center(sp.center),
	radius(sp.radius)
{}
Sphere::Sphere (const glm::vec3& center, float radius):
	Object(),
	center(center),
	radius(radius)
{}

Sphere::~Sphere() 
{}

Sphere* 
Sphere::clone () const {
	return (new Sphere (*this));
}

Sphere& 
Sphere::operator= (const Sphere& rhs) {
	if (this == &rhs) return (*this);
	Object::operator=(rhs); center=rhs.center; radius=rhs.radius;
	return (*this);
}


//@functions
// Hit function
void
Sphere::set_color(const Color& c){
	color = c;
}
void
Sphere::set_color(const float r, const float g, const float b){
	color = Color(r,g,b);
}
bool
Sphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	double 		t;
	glm::vec3	temp 	= ray.o - center;
	double 		a 		= glm::dot(ray.d, ray.d);
	double 		b 		= 2.0 * glm::dot(temp, ray.d);
	double 		c 		= glm::dot(temp, temp) - radius * radius;
	double 		disc	= b * b - 4.0 * a * c;
	
	if (disc < 0.0)
		return(false);
	else {	
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root
	
		if (t > EPSILON) {
			tmin = t;
			sr.normal 	 = (temp + (float)t * ray.d) / radius;
			sr.local_hit_point = ray.o + (float)t * ray.d;
			return (true);
		} 
	
		t = (-b + e) / denom;    // larger root
	
		if (t > EPSILON) {
			tmin = t;
			sr.normal   = (temp + (float)t * ray.d) / radius;
			sr.local_hit_point = ray.o + (float)t * ray.d;
			return (true);
		} 
	}
	
	return (false);
}

glm::vec3
Sphere::get_center(){
	return center;
}

//private------
//@basics(constructor, desturctor, ...)
//@functions

}