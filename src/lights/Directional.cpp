#include "Directional.h"
namespace Engine {
// ---------------------------------------------------------------------- default constructor

Directional::Directional(void)
	: 	Light(),
		ls(1.f),
		color(1.f),
		dir(0, 1, 0)			
{}


// ---------------------------------------------------------------------- dopy constructor

Directional::Directional(const Directional& dl)
	: 	Light(dl),
		ls(dl.ls),
		color(dl.color),
		dir(dl.dir)  		
{}


// ---------------------------------------------------------------------- clone

Light* 
Directional::clone(void) const {
	return (new Directional(*this));
}


// ---------------------------------------------------------------------- assignment operator

Directional& 
Directional::operator= (const Directional& rhs) 	
{
	if (this == &rhs)
		return (*this);
			
	Light::operator= (rhs);
	
	ls		= rhs.ls;
	color 	= rhs.color;
	dir 	= rhs.dir;

	return (*this);
}


// ---------------------------------------------------------------------- destructor																			

Directional::~Directional(void) {}


// ---------------------------------------------------------------------- get_direction
// as this function is virtual, it shouldn't be inlined 

glm::vec3								
Directional::get_direction(ShadeRec& sr) {
	return (dir);
}	

// ------------------------------------------------------------------------------  L

Color
Directional::L(ShadeRec& s) {	
	return (ls * color);
}
}

