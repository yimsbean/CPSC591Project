#include "Bubble2.h"
namespace Engine{
// ---------------------------------------------------------------- default constructor

Bubble2::Bubble2 (void)
	:	Material(),
		bubble_brdf(new Bubble_BRDF)
{}

// ---------------------------------------------------------------- copy constructor

Bubble2::Bubble2(const Bubble2& m)
	: 	Material(m)
{
	if(m.bubble_brdf == nullptr)
		bubble_brdf = m.bubble_brdf->clone();
	else  bubble_brdf = nullptr;
}

// ---------------------------------------------------------------- clone

Material*
Bubble2::clone(void) const {
	return (new Bubble2(*this));
}

// ---------------------------------------------------------------- assignment operator

Bubble2&
Bubble2::operator= (const Bubble2& rhs) {
	if (this == &rhs)
		return (*this);

	Material::operator=(rhs);

	if (bubble_brdf) {
		delete bubble_brdf;
		bubble_brdf = nullptr;
	}
	return (*this);
}

// ---------------------------------------------------------------- destructor

Bubble2::~Bubble2(void){
	if (bubble_brdf) {
		delete bubble_brdf;
		bubble_brdf = nullptr;
	}
}

//normal usage
Color
Bubble2::shade(ShadeRec& sr){
	glm::vec3 	wo 			= -sr.ray.d;
	glm::vec3   wi = sr.w.lights[0]->get_direction(sr);
	Color 	color = bubble_brdf->f(sr,wo,wi);
	
	int num_lights	= sr.w.lights.size();
	for (int j = 0; j < num_lights; j++) {
		glm::vec3 wi = sr.w.lights[j]->get_direction(sr);    
		float ndotwi = glm::dot(sr.normal, wi);
		if (ndotwi > 0.0) 
			color += bubble_brdf->f(sr,wo,wi);
	}
	return color;
}

//only render texture
Color
Bubble2::textureShade(ShadeRec& sr){
	glm::vec3 	wo;	//dummy
	glm::vec3   wi;	//dummy
	return bubble_brdf->f(sr,wo,wi);
}
//only render light
Color
Bubble2::lighting(ShadeRec& sr){
	glm::vec3 	wo 			= -sr.ray.d;
	glm::vec3   wi;
	Color 	color = sr.w.background_color;
	float 	radiance;
	
	for(auto& light: sr.w.lights){
		glm::vec3 wi = light->get_direction(sr);    
		float ndotwi = glm::dot(sr.normal, wi);
		if (ndotwi > 0.0) 
			color += sr.w.background_color;
	}
	return color;
}


}