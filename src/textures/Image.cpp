
#include <iostream>
#include <stdio.h>

#include "Constants.h"   // defines red
#include "Image.h"
namespace Engine{
// ---------------------------------------------------- default constructor

Image::Image(void)
	:	hres(100),
		vres(100)
{}


// ---------------------------------------------------- copy constructor								

Image::Image(const Image& image)
	:	hres(image.hres),
		vres(image.vres),
		pixels(image.pixels)
{}		

Image::Image(const int hres, const int vres)
	:	hres(hres),
		vres(vres)
		//vector.reserve?
{pixels.resize(hres*vres);}		

// ---------------------------------------------------- assignment operator	

Image& 										
Image::operator= (const Image& rhs) {
	if (this == &rhs)
		return (*this);
	hres 		= rhs.hres;
	vres 		= rhs.vres;
	pixels 		= rhs.pixels;
	return (*this);
}		

// ---------------------------------------------------- destructor	

Image::~Image(void)	{}
	



// --------------------------------------------------------------------------------------------- get_color 

Color									
Image::get_color(const int row, const int column) const {
	int index = (column)*hres +  (row);
	int pixels_size = pixels.size();
	if (index < pixels_size){
		return (pixels[index]);
	}
	else{
		return (red);    // useful for debugging 
	}
}

void
Image::set_color(const int row, const int column,const Color c){
	int index = (column)*hres +  (row);
	int pixels_size = pixels.size();
	if (index < pixels_size){
		pixels[index] = c;
	}
}

 
}