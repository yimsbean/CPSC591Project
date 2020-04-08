#include "Triangle.h"
#include "Object.h"
						
namespace Engine{
//#Triangle =========
//public------
//@basics(constructor, desturctor, ...)

//constructor
Triangle::Triangle():
	Object(),
	p1(glm::vec3(0.f)),
	p2(glm::vec3(0.f)),
	p3(glm::vec3(0.f)),
	normal(glm::vec3(0.f,1.f,0.f))
{}
Triangle::Triangle(const Triangle& tr):
	Object(),
	p1(tr.p1),
	p2(tr.p2),
	p3(tr.p3),
	normal(tr.normal)
{}
Triangle::Triangle (const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3):
	Object(),
	p1(p1),
	p2(p2),
	p3(p3)
{calculate_normal();}

Triangle::~Triangle() 
{}

Triangle* 
Triangle::clone () const {
	return (new Triangle (*this));
}

Triangle& 
Triangle::operator= (const Triangle& rhs) {
	if (this == &rhs) return (*this);
	Object::operator=(rhs); p1=rhs.p1; p2=rhs.p2; p3=rhs.p3; normal=rhs.normal;
	return (*this);
}


//@functions
// Hit function
void
Triangle::set_color(const Color& c){
	color = c;
}
void
Triangle::set_color(const float r, const float g, const float b){
	color = Color(r,g,b);
}

bool 															 
Triangle::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	double a = p1.x - p2.x, b = p1.x - p3.x, c = ray.d.x, d = p1.x - ray.o.x; 
	double e = p1.y - p2.y, f = p1.y - p3.y, g = ray.d.y, h = p1.y - ray.o.y;
	double i = p1.z - p2.z, j = p1.z - p3.z, k = ray.d.z, l = p1.z - ray.o.z;
		
	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k, s = e * j - f * i;
	
	double inv_denom  = 1.0 / (a * m + b * q + c * s);
	
	double e1 = d * m - b * n - c * p;
	double beta = e1 * inv_denom;
	
	if (beta < 0.0)
	 	return (false);
	
	double r = r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * inv_denom;
	
	if (gamma < 0.0 )
	 	return (false);
	
	if (beta + gamma > 1.0)
		return (false);
			
	double e3 = a * p - b * r + d * s;
	double t = e3 * inv_denom;
	
	if (t < EPSILON) 
		return (false);
					
	tmin 				= t;
	sr.normal 			= normal;  	
	sr.local_hit_point 	= ray.o + (float)t * ray.d;	
	return (true);
}  

// Hit function for shadow rays
/*
bool
Triangle::shadow_hit(const Ray& ray, double& tmin) const {
	double a = p1.x - p2.x, b = p1.x - p3.x, c = ray.d.x, d = p1.x - ray.o.x; 
	double e = p1.y - p2.y, f = p1.y - p3.y, g = ray.d.y, h = p1.y - ray.o.y;
	double i = p1.z - p2.z, j = p1.z - p3.z, k = ray.d.z, l = p1.z - ray.o.z;
		
	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k, s = e * j - f * i;
	
	double inv_denom  = 1.0 / (a * m + b * q + c * s);
	
	double e1 = d * m - b * n - c * p;
	double beta = e1 * inv_denom;
	
	if (beta < 0.0)
	 	return (false);
	
	double r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * inv_denom;
	
	if (gamma < 0.0)
	 	return (false);
	
	if (beta + gamma > 1.0)
		return (false);
			
	double e3 = a * p - b * r + d * s;
	double t = e3 * inv_denom;
	
	if (t < EPSILON)
		return (false);
					
	tmin = t;
	
	return(true);	
}
*/
//private------
//@basics(constructor, desturctor, ...)
//@functions
void
Triangle::calculate_normal() {	
	normal = glm::normalize(
				glm::cross(p2 - p1,p3 - p1)
			);
}
glm::vec3
Triangle::get_center(){
	return (p1+p2+p3)/3.f;
}
}