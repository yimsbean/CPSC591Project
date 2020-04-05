// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "BTDF.h"
namespace Engine{
// ------------------------------------------------------------------------ default constructor

BTDF::BTDF(void) {}


// ------------------------------------------------------------------------ copy constructor

BTDF::BTDF(const BTDF& btdf) {}


// ------------------------------------------------------------------------ destructor

BTDF::~BTDF(void) {}


// ------------------------------------------------------------------------ assignment operator

BTDF&														
BTDF::operator= (const BTDF& rhs) {
	if (this == &rhs)
		return (*this);

	return (*this);
}


// ------------------------------------------------------------------------ f

Color
BTDF::f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const {
	return (black);
}


// ------------------------------------------------------------------------ sample_f

Color
BTDF::sample_f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi) const {
	return (black);
}


// ------------------------------------------------------------------------ rho	
	
Color
BTDF::rho(const ShadeRec& sr, const glm::vec3& wo) const {
	return (black);
}
}