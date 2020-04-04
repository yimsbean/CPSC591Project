
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
	

// ---------------------------------------------------- read_ppm_file

void										
Image::read_ppm_file(const char* file_name) {

    // read-only binary sequential access
    
    FILE* file = fopen(file_name, "rb");
    
    if (file == 0){
		std::cerr << "could not open file\n";
	}
	//else
	//	std::cout << "file opened\n";

    // PPM header
    
    unsigned char ppm_type;
    if (fscanf(file, "P%c\n", &ppm_type) != 1){
		std::cerr << "Invalid PPM signature\n";
	}
	
    // only binary PPM supported
    
    if (ppm_type != '6'){
		std::cerr << "Only binary PPM supported\n";
	}

    // skip comments
    
    unsigned char dummy;
    while (fscanf(file ,"#%c", &dummy)) 
        while (fgetc(file) != '\n');

    // read image size
    
    if (fscanf(file, "%d %d\n", &hres, &vres) != 2){
		std::cerr << "Invalid image size\n";
	}

    if (hres <= 0)
		std::cerr << "Invalid image width\n";
	//else
	//	std::cout << "hres = " << hres << std::endl;

    
	if (vres <= 0)
		std::cerr << "Invalid image height\n";
	//else
	//	std::cout << "vres = " << vres << std::endl;


    // maximum value to be found in the PPM file (usually 255)
    
    unsigned int max_value;
    if (fscanf(file, "%d\n", &max_value) != 1){
		std::cerr << "Invalid max value\n";
	}

	float inv_max_value = 1.0 / (float)max_value;

    // allocate memory
    
	pixels.reserve(hres * vres);

    // read pixel data
    
    for (unsigned int y = 0; y < vres; y++) {
        for (unsigned int x = 0; x < hres; x++) {
            unsigned char red;
            unsigned char green;
            unsigned char blue;
            
            if (fscanf(file, "%c%c%c", &red, &green, &blue) != 3) {
				std::cerr << "Invalid image\n";
			}

			float r = red   * inv_max_value;
			float g = green * inv_max_value;
			float b = blue  * inv_max_value;

			pixels.push_back(Color(r, g, b));
        }
    }

    // close file
    
    fclose(file);
	
	//std::cout << "finished reading PPM file\n";
}



// --------------------------------------------------------------------------------------------- get_color 

Color									
Image::get_color(const int row, const int column) const {
	int index = column + hres * (vres - row - 1);
	int pixels_size = pixels.size();
	
	if (index < pixels_size)
		return (pixels[index]);
	else
		return (red);    // useful for debugging 
}

 
}