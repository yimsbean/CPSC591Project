#include "Bubble_BRDF.h"
namespace Engine{
// ---------------------------------------------------------------------- default constructor

Bubble_BRDF::Bubble_BRDF(void)
	:   BRDF(),
		cd(new ImageTexture)
{}

// ---------------------------------------------------------- destructor

Bubble_BRDF::~Bubble_BRDF(void) {}


// ---------------------------------------------------------------------- clone

Bubble_BRDF*
Bubble_BRDF::clone(void) const {
	return (new Bubble_BRDF(*this));
}



// ---------------------------------------------------------------------- f

Color
Bubble_BRDF::f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const {
	if(cd == nullptr)
		return black;
	else
		return cd->get_color(sr);
}
// ---------------------------------------------------------- rho

Color
Bubble_BRDF::rho(const ShadeRec& sr, const glm::vec3& wo) const {
	return (black);
}
}