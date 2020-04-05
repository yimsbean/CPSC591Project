#pragma once
// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// this implements perfect specular reflection for indirect illumination
// with reflective materials 

#include "BRDF.h"
#include "Constants.h"

namespace Engine{
class PerfectSpecular: public BRDF 
{
	public:
	
		PerfectSpecular(void);
		
		~PerfectSpecular(void);
		
		virtual PerfectSpecular*
		clone(void) const;
		
		void
		set_kr(const float k);
		
		void
		set_cr(const Color& c);
		
		void													
		set_cr(const float r, const float g, const float b);
		
		void													
		set_cr(const float c);
		
		virtual Color
		f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const;
		
		virtual Color
		sample_f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi) const;
		
		virtual Color
		sample_f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wi, float& pdf) const;
		
		virtual Color
		rho(const ShadeRec& sr, const glm::vec3& wo) const;
				
	private:
	
		float		kr;			// reflection coefficient
		Color 	cr;			// the reflection colour
};


// -------------------------------------------------------------- set_kr

inline void
PerfectSpecular::set_kr(const float k) {
	kr = k;
}


// -------------------------------------------------------------- set_cr

inline void
PerfectSpecular::set_cr(const Color& c) {
	cr = c;
}


// ---------------------------------------------------------------- set_cr

inline void													
PerfectSpecular::set_cr(const float r, const float g, const float b) {
	cr.r = r; cr.g = g; cr.b = b;
}


// ---------------------------------------------------------------- set_cr

inline void													
PerfectSpecular::set_cr(const float c) {
	cr.r = c; cr.g = c; cr.b = c;
}

}