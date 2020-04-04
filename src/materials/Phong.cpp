
#include "Phong.h"

// ---------------------------------------------------------------- default constructor
namespace Engine {
Phong::Phong (void)
	:	Material(),
		ambient_brdf(new Lambertian),
		diffuse_brdf(new Lambertian)
{}



// ---------------------------------------------------------------- copy constructor

Phong::Phong(const Phong& m)
	: 	Material(m)
{
	if(m.ambient_brdf)
		ambient_brdf = m.ambient_brdf->clone(); 
	else  ambient_brdf = NULL;
	
	if(m.diffuse_brdf)
		diffuse_brdf = m.diffuse_brdf->clone(); 
	else  diffuse_brdf = NULL;

}


// ---------------------------------------------------------------- clone

Material*										
Phong::clone(void) const {
	return (new Phong(*this));
}	


// ---------------------------------------------------------------- assignment operator

Phong& 
Phong::operator= (const Phong& rhs) {
	if (this == &rhs)
		return (*this);
		
	Material::operator=(rhs);
	
	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}

	if (rhs.ambient_brdf)
		ambient_brdf = rhs.ambient_brdf->clone();
		
	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}

	if (rhs.diffuse_brdf)
		diffuse_brdf = rhs.diffuse_brdf->clone();

	return (*this);
}


// ---------------------------------------------------------------- destructor

Phong::~Phong(void) {

	if (ambient_brdf) {
		delete ambient_brdf;
		ambient_brdf = NULL;
	}
	
	if (diffuse_brdf) {
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}
}


// ---------------------------------------------------------------- shade

Color
Phong::shade(ShadeRec& sr) {
	glm::vec3 	wo 			= -sr.ray.d;
	Color 	L 			= ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
	int 		num_lights	= sr.w.lights.size();
	
	for (int j = 0; j < num_lights; j++) {
		glm::vec3 wi = sr.w.lights[j]->get_direction(sr);    
		float ndotwi = glm::dot(sr.normal,wi);
	
		if (ndotwi > 0.0) 
			L += diffuse_brdf->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * ndotwi;
	}
	
	return (L);
}

}