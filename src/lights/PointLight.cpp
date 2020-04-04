#include "PointLight.h"

namespace Engine{
PointLight::PointLight()
	: 	Light(),
		ls(1.f),
		color(1.f),
		location(0, 1, 0)			
{}

// ---------------------------------------------------------------------- dopy constructor

PointLight::PointLight(const PointLight& pl)
	: 	Light(pl),
		ls(pl.ls),
		color(pl.color),
		location(pl.location)  		
{}

PointLight::~PointLight(void) {}


Light* 
PointLight::clone(void) const {
	return (new PointLight(*this));
}


// ---------------------------------------------------------------------- assignment operator

PointLight& 
PointLight::operator= (const PointLight& rhs) 	
{
	if (this == &rhs)
		return (*this);
	Light::operator= (rhs);
	ls		= rhs.ls;
	color 	= rhs.color;
	location 	= rhs.location;
	return (*this);
}


glm::vec3
PointLight::get_direction(ShadeRec& sr) {	
	return glm::normalize(location - sr.hit_point);
}
		
Color
PointLight::L(ShadeRec& sr) {	
	return (ls * color);
}
}