#pragma once

#include "Light.h"
#include "Color.h"

#include "ShadeRec.h"

namespace Engine {
class Directional: public Light {
	public:
	
		Directional(void);   							

		Directional(const Directional& dl); 
		
		virtual Light* 									
		clone(void) const;			

		Directional& 									
		operator= (const Directional& rhs); 
			
		virtual											
		~Directional(void); 
				
		void
		scale_radiance(const float b);
		
		void
		set_color(const float c);
		
		void
		set_color(const Color& c);
		
		void
		set_color(const float r, const float g, const float b); 		
			
		void
		set_direction(glm::vec3 d);						
		
		void
		set_direction(float dx, float dy, float dz);
		
		virtual glm::vec3								
		get_direction(ShadeRec& sr);
				
		virtual Color		
		L(ShadeRec& sr);	
		
	private:

		float		ls;			
		Color		color;
		glm::vec3	dir;		// direction the light comes from
};


// inlined access functions


// ------------------------------------------------------------------------------- scale_radiance

inline void
Directional::scale_radiance(const float b) { 
	ls = b;
}

// ------------------------------------------------------------------------------- set_color

inline void
Directional::set_color(const float c) {
	color.r = c; color.g = c; color.b = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
Directional::set_color(const Color& c) {
	color = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
Directional::set_color(const float r, const float g, const float b) {
	color.r = r; color.g = g; color.b = b;
}


// ---------------------------------------------------------------------- set_direction

inline void
Directional::set_direction(glm::vec3 d) {
	dir = glm::normalize(d);
}


// ---------------------------------------------------------------------- set_direction 

inline void
Directional::set_direction(float dx, float dy, float dz) {
	dir.x = dx; dir.y = dy; dir.z = dz;
	dir = glm::normalize(dir);
}


}
