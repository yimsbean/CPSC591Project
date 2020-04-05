#include "Lambertian.h"

namespace Engine{
//#Lambertian =========
//public ------
//@basics(constructor, desturctor, ...)

//constructor
Lambertian::Lambertian():
	BRDF(),
	kd(0.f), 
	cd(0.f)
{}
Lambertian::Lambertian(const Lambertian& lamb):
	BRDF(lamb),
	kd(lamb.kd), 
	cd(lamb.cd)
{}

//destructor
Lambertian::~Lambertian() 
{}

//clone
Lambertian* 
Lambertian::clone() const {
	return (new Lambertian(*this));
}	

//@functions
Color
Lambertian::f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const {
	return (kd * cd / M_PI);
}


Color
Lambertian::rho(const ShadeRec& sr, const glm::vec3& wo) const {
	return (kd * cd);
}

}
