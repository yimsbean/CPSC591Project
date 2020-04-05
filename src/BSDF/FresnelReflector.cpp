// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "FresnelReflector.h"
namespace Engine{
// ---------------------------------------------------------- default constructor

FresnelReflector::FresnelReflector(void)
	: 	BRDF(),
		eta_in(0.0), 
		eta_out(1.0)
{}
FresnelReflector::FresnelReflector(const FresnelReflector& fr)
	: 	BRDF(fr),
		eta_in(fr.eta_in), 
		eta_out(fr.eta_out)
{}
// ---------------------------------------------------------- destructor

FresnelReflector::~FresnelReflector(void) {}


// ---------------------------------------------------------------------- clone

FresnelReflector* 
FresnelReflector::clone(void) const {
	return (new FresnelReflector(*this));
}	


// ---------------------------------------------------------- f

Color
FresnelReflector::f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const {
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
    Color test = white / fabs(glm::dot(sr.normal,wr));
    //std::cout<<"REFELCTOR : [" <<fresnel(sr)<< "]\n";
	return (fresnel(sr) * white / fabs(glm::dot(sr.normal,wr)));
}


// ----------------------------------------------------------------------------------------- fresnel
// from Listing 18.1

float
FresnelReflector::fresnel(const ShadeRec& sr) const {
	glm::vec3 normal(sr.normal);
	float ndotd = -glm::dot(normal, sr.ray.d);
	float eta;
	
	if (ndotd < 0.0) { 
		normal = -normal;
		eta = eta_out / eta_in;
	}
	else
		eta = eta_in / eta_out;

	float cos_theta_i 		= -glm::dot(normal, sr.ray.d); 
	float temp 				= 1.0 - (1.0 - cos_theta_i * cos_theta_i) / (eta * eta);
	float cos_theta_t 		= sqrt (1.0 - (1.0 - cos_theta_i * cos_theta_i) / (eta * eta));
	float r_parallel 		= (eta * cos_theta_i - cos_theta_t) / (eta * cos_theta_i + cos_theta_t);
	float r_perpendicular 	= (cos_theta_i - eta * cos_theta_t) / (cos_theta_i + eta * cos_theta_t);
	float kr 				= 0.5 * (r_parallel * r_parallel + r_perpendicular * r_perpendicular);
	

	return (kr);
}

// ---------------------------------------------------------- rho

Color
FresnelReflector::rho(const ShadeRec& sr, const glm::vec3& wo) const {
	return (black);
}

}