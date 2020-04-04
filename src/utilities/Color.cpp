#include "Color.h"

namespace Engine{
// -------------------------------------------------------- default constructor

Color::Color(void)
	: a(0.0), r(0.0), g(0.0), b(0.0) 							
{}


// -------------------------------------------------------- constructor

Color::Color(float c)
	: r(c), g(c), b(c) 							
{}
								

// -------------------------------------------------------- constructor

Color::Color(float r, float g, float b)	
	: r(r), g(g), b(b)
{}


// -------------------------------------------------------- copy constructor

Color::Color(const Color& c)
	: a(c.a),r(c.r), g(c.g), b(c.b)
{} 				 

// STRING
Color::Color(const int hex): 
	a(((hex >> 24) & 0xFF) / 255.0),
	r(((hex >> 16) & 0xFF) / 255.0),
	g(((hex >> 8) 	& 0xFF) / 255.0),
	b(((hex) 		& 0xFF) / 255.0)
{} 				 
		


// -------------------------------------------------------- destructor

Color::~Color(void)		
{}


// --------------------------------------------------------assignment operator

Color& 											
Color::operator= (const Color& rhs) {
	if (this == &rhs) return (*this);
	a = rhs.a; r = rhs.r; g = rhs.g; b = rhs.b;
	return (*this);
}
}