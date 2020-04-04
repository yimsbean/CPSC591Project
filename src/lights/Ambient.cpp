
#include "Ambient.h"
namespace Engine {
// ---------------------------------------------------------------------- default constructor

Ambient::Ambient (void)
	: 	Light(),
		ls(1.f),
		color(1.f)			
{}


// ---------------------------------------------------------------------- copy constructor

Ambient::Ambient (const Ambient& a)
	: 	Light(a),
		ls(a.ls),
		color(a.color) 		
{}


// ---------------------------------------------------------------------- clone

Light* 
Ambient::clone(void) const {
	return (new Ambient(*this));
}	


// ---------------------------------------------------------------------- assignment operator

Ambient& 
Ambient::operator= (const Ambient& rhs) {
	if (this == &rhs)
		return (*this);
			
	Light::operator= (rhs);
	
	ls 		= rhs.ls;
	color 	= rhs.color;
	
	return (*this);
}


// ---------------------------------------------------------------------- destructor																			

Ambient::~Ambient (void) {}


// ---------------------------------------------------------------------- get_direction	

glm::vec3								
Ambient::get_direction(ShadeRec& s) {
	return (glm::vec3(0.0));
}


// ---------------------------------------------------------------------- L

Color
Ambient::L(ShadeRec& sr) {	
	return (ls * color);
}


}