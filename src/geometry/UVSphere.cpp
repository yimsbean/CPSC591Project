#include "UVSphere.h"
#include "Object.h"
						
namespace Engine{
//#UVSphere =========
//public------
//@basics(constructor, desturctor, ...)

//constructor
UVSphere::UVSphere():
	Object(),
	center(glm::vec3(0.f)),
	radius(1.f),
	cameraLocation(0.f)
{}
UVSphere::UVSphere(const UVSphere& sp):
	Object(),
	center(sp.center),
	radius(sp.radius),
	cameraLocation(sp.cameraLocation)
{}
UVSphere::UVSphere (const glm::vec3& center, float radius, const glm::vec3& cameraLocation):
	Object(),
	center(center),
	radius(radius),
	cameraLocation(cameraLocation)
{}

UVSphere::~UVSphere() 
{}

UVSphere* 
UVSphere::clone () const {
	return (new UVSphere (*this));
}

UVSphere& 
UVSphere::operator= (const UVSphere& rhs) {
	if (this == &rhs) return (*this);
	Object::operator=(rhs); center=rhs.center; radius=rhs.radius; cameraLocation = rhs.cameraLocation;
	return (*this);
}


//@functions
// Hit function
void
UVSphere::set_color(const Color& c){
	color = c;
}
void
UVSphere::set_color(const float r, const float g, const float b){
	color = Color(r,g,b);
}
bool
UVSphere::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
	double 		t;
	glm::vec3	temp 	= ray.o - center;
	double 		a 		= glm::dot(ray.d, ray.d);
	double 		b 		= 2.0 * glm::dot(temp, ray.d);
	double 		c 		= glm::dot(temp, temp) - radius * radius;
	double 		disc	= b * b - 4.0 * a * c;
	
	if (disc < 0.0)
		return(false);
		
	double e = sqrt(disc);
	double denom = 2.0 * a;
	t = (-b - e) / denom;    // smaller root

	if (t > EPSILON) {
		tmin = t;
		sr.normal 	 = (temp + (float)t * ray.d) / radius;
		sr.local_hit_point = ray.o + (float)t * ray.d;
		
		//UV Mapping
		
		glm::vec3 xyz = sr.normal;
		float x = xyz.x;
		float y = xyz.y;
		float z = xyz.z;
		
		//float PHI = glm::atan(y/x);
		//float THETA = glm::acos(z);

		
		// -PI <= THETA <= PI  , -PI/2 <= PHI <= PI/2
		
		float PHI = glm::asin(y);
		float xdivcosphi = x/glm::cos(PHI);
		float THETA;
		if(xdivcosphi > -1.f && xdivcosphi < 1.f){
			THETA = glm::acos(xdivcosphi);
		}else{
			THETA = glm::acos(1); // == 0
		}

		
		//0 ~ M_PI/2
		if(x>=0 && z>=0)
			THETA *= 1;
		//M_PI/2 ~ M_PI
		else if(x<0 && z>=0)
			THETA *= 1;
		//0 ~ -M_PI/2
		else if(x>=0 && z<0)
			THETA *= -1;
		//-M_PI/2 ~ -M_PI
		else if(x<0 && z<0)
			THETA *= -1;
		
		//-M_PI ~ M_PI
		//-1 <= x,y <= 1
		float dx = THETA / M_PI;
		float dy = PHI * 2.f / M_PI;
		//if(x > 0 && z > 0 &&dx > 0)
		//	std::cout<<dx<<"\n";

		//0 <= u, v <= 1
		//float u = 0.25*(dx+1.f)/2.f;
		float u = (dx+1.f)/2.f;
		float v = (dy+1.f)/2.f;
		//if(x<0 && z>=0 && u > 0.75f)
		//	std::cout<<x<<","<<y<<","<<z<<" <xyz> "<<PHI<<","<<THETA<<" {PT} " <<dx <<","<<dy<<" [dxdy] "<<u <<","<<v<<" =uv\n";

		/*
		// CUBE MAPPING(x*4, y*3)
		//0 <= u <= 0.25, 0 <= v <= 0.333
		u *= 0.25;
		v *= 0.333;
		//https://en.wikipedia.org/wiki/Cube_mapping
		float absX = fabs(x);
		float absY = fabs(y);
		float absZ = fabs(z);
		
		bool isXPositive = x > 0;
		bool isYPositive = y > 0;
		bool isZPositive = z > 0;
		//-------------------------------
		
		// POSITIVE Z (FRONT), CASE 0
		if (isZPositive && absZ >= absX && absZ >= absY) {
			u += 0.25;
			v += 0.333;
		}
		// NEGATIVE Z (BACK), CASE 1
		else if (!isZPositive && absZ >= absX && absZ >= absY) {
			u += 0.25*3;
			v += 0.333;
		}
		// POSITIVE Y (UP), CASE 2
		else if (isYPositive && absY >= absX && absY >= absZ) {
			u += 0.25;
			v += 0.333*2;
		}
		// NEGATIVE Y (DOWN), CASE 3
		else if (!isYPositive && absY >= absX && absY >= absZ) {
			u += 0.25;
			//v += 0;
		}
		// POSITIVE X (RIGHT), CASE 4
		else if (isXPositive && absX >= absY && absX >= absZ) {
			u += 0.25*2;
			v += 0.333;
		}
		// NEGATIVE X (LEFT), CASE 5
		else if (!isXPositive && absX >= absY && absX >= absZ) {
			//u += 0;
			v += 0.333;
		}else{
			std::cerr<< "[" << u <<","<<v <<"] ERR\n";
		}
		*/

		//-------------------------------
		//apply
		if(u >= 0.f && u <= 1.f && v >= 0.f && v <= 1.f){
			sr.u = u;
			sr.v = v;
		}
		return (true);
	} 

	t = (-b + e) / denom;    // larger root
	if (t > EPSILON) {
		tmin = t;
		sr.normal   = (temp + (float)t * ray.d) / radius;
		sr.local_hit_point = ray.o + (float)t * ray.d;
		return (true);
	}
	return (false);
}

glm::vec3
UVSphere::get_center(){
	return center;
}

//private------
//@basics(constructor, desturctor, ...)
//@functions

}