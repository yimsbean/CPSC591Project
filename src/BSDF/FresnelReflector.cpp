// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "FresnelReflector.h"
namespace Engine{
// ---------------------------------------------------------- default constructor

FresnelReflector::FresnelReflector(void)
	: 	BRDF(),
		eta(1.0)
{}
FresnelReflector::FresnelReflector(const FresnelReflector& fr)
	: 	BRDF(fr),
		eta(fr.eta)
{}
// ---------------------------------------------------------- destructor

FresnelReflector::~FresnelReflector(void) {}


// ---------------------------------------------------------------------- clone

FresnelReflector* 
FresnelReflector::clone(void) const {
	return (new FresnelReflector(*this));
}	
FresnelReflector&							
FresnelReflector::operator= (const FresnelReflector& rhs) {
	if (this == &rhs)
		return (*this);
	eta = rhs.eta;
	return (*this);
}     

// ---------------------------------------------------------- f

Color
FresnelReflector::f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const {
	return (black);
}

// ---------------------------------------------------------- rho

Color
FresnelReflector::rho(const ShadeRec& sr, const glm::vec3& wo) const {
	return (black);
}


// ---------------------------------------------------------- sample_f
// this computes wi: the direction of perfect mirror reflection
// it's called from from the functions Reflective::shade and Transparent::shade.
// the fabs in the last statement is for transparency


// ----------------------------------------------------------------------------------------- sample_f

Color
FresnelReflector::sample_f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wr) const {
	float ndotwo = glm::dot(sr.normal, wo);
	wr = -wo + 2.f * sr.normal * ndotwo; 
	return (fresnel(sr) * white / fabs(glm::dot(sr.normal,wr)));
}


// ----------------------------------------------------------------------------------------- fresnel
// from Listing 18.1

float
FresnelReflector::fresnel(const ShadeRec& sr) const {
	glm::vec3 normal(sr.normal);
	float ndotd = -glm::dot(normal, sr.ray.d);
	float e = eta;
	
	if (ndotd < 0.0) { 
		normal = -normal;
		e = 1 / e;
	}

	float cos_theta_i 		= -glm::dot(normal, sr.ray.d); 
	float cos_theta_t 		= sqrt (1.0 - (1.0 - cos_theta_i * cos_theta_i) / (e * e));
	float r_parallel 		= (e * cos_theta_i - cos_theta_t) / (e * cos_theta_i + cos_theta_t);
	float r_perpendicular 	= (cos_theta_i - e * cos_theta_t) / (cos_theta_i + e * cos_theta_t);
	float kr 				= 0.5 * (r_parallel * r_parallel + r_perpendicular * r_perpendicular);
	

	return (kr);
}

}