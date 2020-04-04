#include "GGXSpecular.h"
//Specular for GGX/Trowbridge-Reitz
namespace Engine{
//constructor
GGXSpecular::GGXSpecular():
	kr(0.f),
	cr(Color(0.f)),
	r(0.5f)
{}

//destructor
GGXSpecular::~GGXSpecular()
{}

//clone
GGXSpecular* 
GGXSpecular::clone (void) const {
	return (new GGXSpecular(*this));
}


//@functions
// f
// this is used for direct illumination only

Color
GGXSpecular::f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const {
	Color 	L; 
	//std::vec3 	r(-wi + 2.0 * sr.normal * ndotwi); // mirror reflection direction
	//float 		rdotwo = r * wo;
	Color		f0 = cr;
    float       pi = 3.1415936;
	glm::vec3   wh = glm::normalize(wi + wo);
    float       k = (r+1)*(r+1)/8;

    float       alpha = r*r;
    float       alpha2 = alpha*alpha;
    float       ndotwh = glm::dot(sr.normal,wh);
    float       ndotwh2 = ndotwh*ndotwh;
    float       whdotwi = glm::dot(wh,wi);
    float       whdotwo = glm::dot(wh,wo);

	float D = alpha2 /(pi * ((ndotwh2)*(alpha2-1)+1)*((ndotwh2)*(alpha2-1)+1));
	float G = (1/(whdotwi*(1-k)+k))*(1/(whdotwo*(1-k)+k));
	Color F = f0 + (Color(1.f)-f0)*pow((1-whdotwi),5);
	float LEFT = 4*glm::dot(glm::dot(sr.normal,wi),glm::dot(sr.normal,wo));
	L = F * G * D / LEFT;

	return (L);
}

//rho
Color
GGXSpecular::rho(const ShadeRec& sr, const glm::vec3& wo) const {
	return ka*cr;
}

}