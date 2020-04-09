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

Color
Color::powc(float p) const {
	return (Color(std::pow(r, p), std::pow(g, p), std::pow(b, p)));
}

//An RGB to Spectrum Conversion forReflectances
//deprecated
float
colortowave(Color c){
	//visuble spectrum = 380~740 nm
	float redSpectrum = 700;//nm 
	float greenSpectrum = 546.1;//nm 
	float blueSpectrum = 435.8;//nm

	float magentaSpectrum = 567;//nm red+blue (SHOULDN't have wavelength)
	float cyanSpectrum = 505;	//nm green+blue
	float yellowSpectrum = 580;	//nm red+green
	
	float whiteSpectrum = 1.f;

	float red = c.r;	//0~1
	float green = c.g;	//0~1
	float blue = c.b;	//0~1

	float ret = 0;
	if(red<=green && red<=blue){
		ret += red * whiteSpectrum;
		if(green<=blue){
			ret += (green - red) * cyanSpectrum;
			ret += (blue - green) * blueSpectrum;
		}
		else{
			ret += (blue - red) * cyanSpectrum;
			ret += (green - blue) * greenSpectrum;
		}
	}
	else if(green<=red && green<=blue){
		ret += green * whiteSpectrum;
		if(blue<=red){
			ret += (blue - green) * magentaSpectrum;
			ret += (red - blue) * redSpectrum;
		}
		else{
			ret += (red - green) * magentaSpectrum;
			ret += (blue - red) * blueSpectrum;
		}
	}
	else {// blue<=red && blue<=green
		ret += blue * whiteSpectrum;
		if(red<=green){
			ret += (red - blue) * yellowSpectrum;
			ret += (green - red) * greenSpectrum;
		}
		else{
			ret += (blue - blue) * yellowSpectrum;
			ret += (red - green) * redSpectrum;
		}
	}
	return ret;
}
//deprecated
Color
wavetocolor(float l){
	//visuble spectrum = 380~740 nm
	float redSpectrum = 700;//nm 
	float greenSpectrum = 546.1;//nm 
	float blueSpectrum = 435.8;//nm
	
	float r=0,g=0,b=0,t=0;
	//https://stackoverflow.com/questions/3407942/rgb-values-of-visible-spectrum


	//RED
	if ((l>=400.0)&&(l<410.0)) { 		t=(l-400.0)/(410.0-400.0); r=    +(0.33*t)-(0.20*t*t); }
    else if ((l>=410.0)&&(l<475.0)) { 	t=(l-410.0)/(475.0-410.0); r=0.14         -(0.13*t*t); }
    else if ((l>=545.0)&&(l<595.0)) { 	t=(l-545.0)/(595.0-545.0); r=    +(1.98*t)-(     t*t); }
    else if ((l>=595.0)&&(l<650.0)) { 	t=(l-595.0)/(650.0-595.0); r=0.98+(0.06*t)-(0.40*t*t); }
    else if ((l>=650.0)&&(l<700.0)) { 	t=(l-650.0)/(700.0-650.0); r=0.65-(0.84*t)+(0.20*t*t); }
	
	//GREEN
         if ((l>=415.0)&&(l<475.0)) { 	t=(l-415.0)/(475.0-415.0); g=             +(0.80*t*t); }
    else if ((l>=475.0)&&(l<590.0)) { 	t=(l-475.0)/(590.0-475.0); g=0.8 +(0.76*t)-(0.80*t*t); }
    else if ((l>=585.0)&&(l<639.0)) { 	t=(l-585.0)/(639.0-585.0); g=0.84-(0.84*t)           ; }
	
	//BLUE
         if ((l>=400.0)&&(l<475.0)) { 	t=(l-400.0)/(475.0-400.0); b=    +(2.20*t)-(1.50*t*t); }
    else if ((l>=475.0)&&(l<560.0)) { 	t=(l-475.0)/(560.0-475.0); b=0.7 -(     t)+(0.30*t*t); }
	return Color(r,g,b);
}


}