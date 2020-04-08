#pragma once

#include "Light.h"

namespace Engine {
class Ambient: public Light {
	public:
	
		Ambient(void);   							

		Ambient(const Ambient& a); 					 
	
		virtual Light* 									
		clone(void) const;	
		
		Ambient& 									
		operator= (const Ambient& rhs);									
		
		virtual 									
		~Ambient(void);
				
		void
		scale_radiance(const float b);
		
		void
		set_color(const float c);
		
		void
		set_color(const Color& c);
		
		void
		set_color(const float r, const float g, const float b); 
		
		virtual glm::vec3								
		get_direction(ShadeRec& s); 

		virtual float 
		get_radiance();

		virtual Color
		L(ShadeRec& s);
	
	private:
	
		float		ls;
		Color		color;
};

inline float 
Ambient::get_radiance(){
	return ls;
}


// ------------------------------------------------------------------------------- scale_radiance

inline void
Ambient::scale_radiance(const float b) { 
	ls = b;
}

// ------------------------------------------------------------------------------- set_color

inline void
Ambient::set_color(const float c) {
	color.r = c; color.g = c; color.b = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
Ambient::set_color(const Color& c) {
	color = c;
}


// ------------------------------------------------------------------------------- set_color

inline void
Ambient::set_color(const float r, const float g, const float b) {
	color.r = r; color.g = g; color.b = b;
}

}