#include "Light.h"

namespace Engine {
// ---------------------------------------------------------------------- default constructor

Light::Light(void) {}

// ---------------------------------------------------------------------- dopy constructor

Light::Light(const Light& ls) {}


// ---------------------------------------------------------------------- assignment operator

Light& 
Light::operator= (const Light& rhs) {
	if (this == &rhs)
		return (*this);

	return (*this);
}


// ---------------------------------------------------------------------- destructor

Light::~Light(void) {} 



// ---------------------------------------------------------------------- L
// returns the radiance
Color								
Light::L(ShadeRec& s) {
	//sr.w.ambient_ptr->L(sr) = white light (1, 1, 1)
	return (white);
}


}