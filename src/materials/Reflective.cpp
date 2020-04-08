// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Reflective.h"
namespace Engine{
// ---------------------------------------------------------------- default constructor

Reflective::Reflective (void)
	:	Phong(),
		reflective_brdf(new PerfectSpecular)
{}


// ---------------------------------------------------------------- copy constructor

Reflective::Reflective(const Reflective& rm)
	: 	Phong(rm) {
	
	if(rm.reflective_brdf)
		reflective_brdf = rm.reflective_brdf->clone(); 
	else  
		reflective_brdf = NULL;
}


// ---------------------------------------------------------------- assignment operator

Reflective& 
Reflective::operator= (const Reflective& rhs) {
	if (this == &rhs)
		return (*this);
		
	Phong::operator=(rhs);
	
	if (reflective_brdf) {
		delete reflective_brdf;
		reflective_brdf = NULL;
	}

	if (rhs.reflective_brdf)
		reflective_brdf = rhs.reflective_brdf->clone();

	return (*this);
}


// ---------------------------------------------------------------- clone

Reflective*										
Reflective::clone(void) const {
	return (new Reflective(*this));
}	


// ---------------------------------------------------------------- destructor

Reflective::~Reflective(void) {
	if (reflective_brdf) {
		delete reflective_brdf;
		reflective_brdf = NULL;
	}
}


// ------------------------------------------------------------------------------------ shade 

Color
Reflective::shade(ShadeRec& sr) {	
	Color L(Phong::shade(sr));  // direct illumination
	
	glm::vec3 wo = -sr.ray.d;
	glm::vec3 wi;	
	Color fr = reflective_brdf->sample_f(sr, wo, wi); 
	Ray reflected_ray(sr.hit_point, wi); 
	//reflected_ray.depth = sr.depth + 1;
	
	L += fr * sr.w.background_tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * glm::dot(sr.normal,wi);
					
	return (L);
}
}


