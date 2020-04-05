// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "PerfectSpecular.h"
namespace Engine{
// ---------------------------------------------------------- default constructor

PerfectSpecular::PerfectSpecular(void)
	: 	BRDF(),
		kr(0.0), 
		cr(1.f)
{}

// ---------------------------------------------------------- destructor

PerfectSpecular::~PerfectSpecular(void) {}


// ---------------------------------------------------------------------- clone

PerfectSpecular* 
PerfectSpecular::clone(void) const {
	return (new PerfectSpecular(*this));
}	


// ---------------------------------------------------------- f

Color
PerfectSpecular::f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const {
	return (black);
}


// ---------------------------------------------------------- sample_f
// this computes wi: the direction of perfect mirror reflection
// it's called from from the functions Reflective::shade and Transparent::shade.
// the fabs in the last statement is for transparency

Color
PerfectSpecular::sample_f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi) const {
	float ndotwo = glm::dot(sr.normal, wo);
	wi = -wo + sr.normal * 2.f * ndotwo; 
	return (kr * cr / fabs( glm::dot(sr.normal, wi))); // why is this fabs? // kr would be a Fresnel term in a Fresnel reflector
}											 // for transparency when ray hits inside surface?, if so it should go in Chapter 24


// ---------------------------------------------------------- sample_f
// this version of sample_f is used with path tracing
// it returns ndotwi in the pdf

Color
PerfectSpecular::sample_f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi, float& pdf) const {
	float ndotwo = glm::dot(sr.normal, wo);
	wi = -wo + sr.normal * 2.f * ndotwo; 
	pdf = fabs(glm::dot(sr.normal, wi));
	return (kr * cr);  
}

// ---------------------------------------------------------- rho

Color
PerfectSpecular::rho(const ShadeRec& sr, const glm::vec3& wo) const {
	return (black);
}

}