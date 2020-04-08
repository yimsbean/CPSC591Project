// ------------------------------------------------------------------- default constructor
// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "FresnelTransmitter.h"
namespace Engine{
// ------------------------------------------------------------------- default constructor

FresnelTransmitter::FresnelTransmitter(void)
	: 	BTDF(),
		eta(1.0)
{}


// ------------------------------------------------------------------- copy constructor

FresnelTransmitter::FresnelTransmitter(const FresnelTransmitter& ft)
	: 	BTDF(ft),
		eta(ft.eta)
{}

// ------------------------------------------------------------------- destructor

FresnelTransmitter::~FresnelTransmitter(void) {}



// ------------------------------------------------------------------- clone

FresnelTransmitter* 
FresnelTransmitter::clone(void) {
	return (new FresnelTransmitter(*this));
}


// ------------------------------------------------------------------- assignment operator
		
FresnelTransmitter&							
FresnelTransmitter::operator= (const FresnelTransmitter& rhs) {
	if (this == &rhs)
		return (*this);
	eta = rhs.eta;
	return (*this);
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     

// ------------------------------------------------------------------- f

Color
FresnelTransmitter::f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const {
	return (black);
}
// ------------------------------------------------------------------- rho

Color
FresnelTransmitter::rho(const ShadeRec& sr, const glm::vec3& wo) const {
	return (black);
}
// ------------------------------------------------------------------- tir
// tests for total internal reflection

bool													
FresnelTransmitter::tir(const ShadeRec& sr) const {
	glm::vec3 wo(-sr.ray.d); 
	float cos_thetai = glm::dot(sr.normal,wo); 
	float e = eta;

	if (cos_thetai < 0.0) {
		e = 1 / e;
	}
		
	return (1.0 - (1.0 - cos_thetai * cos_thetai) / (e * e) < 0.0);
}	



// ------------------------------------------------------------------- sample_f
// this computes the direction wt for perfect transmission
// and returns the transmission coefficient
// this is only called when there is no total internal reflection

Color
FresnelTransmitter::sample_f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wt) const {
	
	glm::vec3 normal(sr.normal);
	float ndotwo = glm::dot(normal, wo);
	float e = eta;
		
	if (ndotwo < 0.0) {			// transmitted ray is outside  
		normal = -normal;  					// reverse direction of normal
		e = 1 / e; 			// invert ior 
	}
    float cos_theta_i = glm::dot(normal, wo);
	float cos_theta_t = sqrt (1.0 - (1.0 - cos_theta_i * cos_theta_i) / (e * e));
	wt = -wo / e - (cos_theta_t - cos_theta_i / e) * normal;   

	return (fresnel(sr) / (eta * eta) * white / fabs(glm::dot(sr.normal, wt)));
}

float
FresnelTransmitter::fresnel(const ShadeRec& sr) const {
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
	//k_r = 1/2 (r_parallel^2 + r_perpendicular^2)
	float kr 				= 0.5 * (r_parallel * r_parallel + r_perpendicular * r_perpendicular);
	
	//k_t = 1-k_r	(conservation of energy)
	return (1-kr);
}

}