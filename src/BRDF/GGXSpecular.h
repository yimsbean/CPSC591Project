#pragma once

#include "BRDF.h"
namespace Engine{
class GGXSpecular: public BRDF {
	public:
		GGXSpecular();
		~GGXSpecular();
		
		virtual GGXSpecular*
		clone() const;
		
		void
		set_ka(const float k);
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
		rho(const ShadeRec& sr, const glm::vec3& wo) const;
				
	private:
		float		ka;
		float		kr;			// reflection coefficient
		Color 		cr;			// the reflection colour

		float		r;			//roughness
};

inline void
GGXSpecular::set_ka(const float k) {
	ka = k;
}
// -------------------------------------------------------------- set_kr
inline void
GGXSpecular::set_kr(const float k) {
	kr = k;
}


// -------------------------------------------------------------- set_cr
inline void
GGXSpecular::set_cr(const Color& c) {
	cr = c;
}
inline void													
GGXSpecular::set_cr(const float r, const float g, const float b) {
	cr.r = r; cr.g = g; cr.b = b;
}
inline void													
GGXSpecular::set_cr(const float c) {
	cr.r = c; cr.g = c; cr.b = c;
}

}
