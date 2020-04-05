
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
class FresnelReflector: public BRDF 
{
	public:
	
		FresnelReflector(void);
		
        FresnelReflector(const FresnelReflector& fr);

		~FresnelReflector(void);
		
		virtual FresnelReflector*
		clone(void) const;
		
		void
		set_eta_in(const float ei);
		
		void
		set_eta_out(const float eo);
		
		virtual Color
		f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const;
		
		virtual Color
        sample_f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wr) const;
		
        virtual float
        fresnel(const ShadeRec& sr) const;

		virtual Color
		rho(const ShadeRec& sr, const glm::vec3& wo) const;
				
	private:
	
		float   eta_in;
        float   eta_out;
};


inline void
FresnelReflector::set_eta_in(const float ei) {
	eta_in = ei;
}

// -------------------------------------------------------------- set_ior

inline void
FresnelReflector::set_eta_out(const float eo) {
	eta_out = eo;
}
}
