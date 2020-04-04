#include "BRDF.h"

namespace Engine{
//#BRDF =========
//public ------
//@basics(constructor, desturctor, ...)

//constructor
BRDF::BRDF() 
{}
BRDF::BRDF(const BRDF& brdf) 
{}

//destructor
BRDF::~BRDF() 
{}  

//operator(=)
BRDF&														
BRDF::operator= (const BRDF& rhs) {
	return (*this);
}

//@functions
Color
BRDF::f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const {
	return (black);
}

Color
BRDF::rho(const ShadeRec& sr, const glm::vec3& wo) const {
	return (black);
}

}
