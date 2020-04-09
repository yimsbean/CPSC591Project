#pragma once
#include <cmath>
#include <string>

namespace Engine{
class Color {
	public:
		float a, r, g, b;
	
		Color(void);										// default constructor
		Color(float c);									// constructor
		Color(float r, float g, float b);				// constructor
		Color(const Color& c); 						// copy constructor
		Color(const int hex);
		
		~Color(void);									// destructor
		
		Color& 											// assignment operator
		operator= (const Color& color); 

		Color 											// MINUS!
		operator- (const Color& c) const;	

		Color 											// addition
		operator+ (const Color& c) const;	

		Color& 											// compound addition
		operator+= (const Color& c);
		
		Color 											// multiplication by a float on the right
		operator* (const float a) const;
		
		Color& 											// compound multiplication by a float on the right
		operator*= (const float a);					
				
		Color 											// division by a float
		operator/ (const float a) const;
		
		Color& 											// compound division by a float
		operator/= (const float a); 
				
		Color 											// component-wise multiplication
		operator* (const Color& c) const;
		
		bool												// are two RGBColours the same?
		operator== (const Color& c) const;		

		Color											// raise components to a power
		powc(float p) const;
		
		float												// the average of the components
		average(void) const;		
};

static const Color black = Color(0.f,0.f,0.f);
static const Color red 	= Color(1.f,0.f,0.f);
static const Color white = Color(1.f,1.f,1.f);
static const Color grey = Color(0.1f,0.1f,0.1f);



// inlined member functions

// ----------------------------------------------------------------------- operator-
// addition of two colors
inline Color 
Color::operator- (const Color& c) const {
	return (Color(c.r - r, c.g - g,c.b - b ));
}

// ----------------------------------------------------------------------- operator+
// addition of two colors

inline Color 
Color::operator+ (const Color& c) const {
	return (Color(r + c.r, g + c.g, b + c.b));
}


// ----------------------------------------------------------------------- operator+=
// compound addition of two colors

inline Color& 
Color::operator+= (const Color& c) {
	r += c.r; g += c.g; b += c.b;
    return (*this);
}


// ----------------------------------------------------------------------- operator*
// multiplication by a float on the right

inline Color 
Color::operator* (const float a) const {
	return (Color (r * a, g * a, b * a));	
}


// ----------------------------------------------------------------------- operator*=
// compound multiplication by a float on the right

inline Color& 
Color::operator*= (const float a) {
	r *= a; g *= a; b *= a;
	return (*this);
}


// ----------------------------------------------------------------------- operator/
// division by float

inline Color 
Color::operator/ (const float a) const {
	return (Color (r / a, g / a, b / a));
}


// ----------------------------------------------------------------------- operator/=
// compound division by float

inline Color& 
Color::operator/= (const float a) {	
	r /= a; g /= a; b /= a;
	return (*this);
}



// ----------------------------------------------------------------------- operator*
// component-wise multiplication of two colors

inline Color 
Color::operator* (const Color& c) const {
	return (Color (r * c.r, g * c.g, b * c.b));
} 


// ----------------------------------------------------------------------- operator==
// are two Colors the same?

inline bool
Color::operator== (const Color& c) const {
	return (r == c.r && g == c.g && b == c.b);
}




// inlined non-member function

// ----------------------------------------------------------------------- operator*
// multiplication by a float on the left

inline Color 
operator* (const float a, const Color& c) {
	return (Color (a * c.r, a * c.g, a * c.b));	
}

inline float											
Color::average(void) const {
	return (0.333333333333 * (r + g + b));
}

//deprecated
float
colortowave(Color c);
//deprecated
Color
wavetocolor(float l);

}