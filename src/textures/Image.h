// 	Copyright (C) Kevin Suffern 2000-2007.
// 	Copyright (C) Stefan Brumme 2005.
// 	Copyright (C) Sverre Kvaale 2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

// This is not a texture
// The Image class stores an image in PPM format
// This is used for image based textures, including ramp textures such as marble and sandstone
// I originally chose the PPM format because it's simple to parse
#pragma once

#include <vector>		
#include "Color.h"

//--------------------------------------------------------------------- class Image
namespace Engine{
class Image {	
	public:
	
		Image(void);								

		Image(const int hres, const int vres);

		Image(const Image& image);					

		Image& 										
		operator= (const Image& image);		

		~Image(void) ;								
		
		int
		get_hres(void);	
		
		int
		get_vres(void);	
				
		Color									
		get_color(const int row, const int col) const;		
		
		void
		set_color(const int row, const int col,const Color c);
	private:
		int 					hres;			// horizontal resolution of image
		int						vres;			// vertical resolution of image
		std::vector<Color> 		pixels;
};


//--------------------------------------------------------------------- get_hres

inline int
Image::get_hres(void) {
	return (hres);
}


//--------------------------------------------------------------------- get_vres

inline int
Image::get_vres(void) {
	return (vres);
}
}