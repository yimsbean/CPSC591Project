
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
//used in bubble(material)
class FresnelReflector: public BRDF 
{
	public:
	
		FresnelReflector(void);
		
        FresnelReflector(const FresnelReflector& fr);

		virtual ~FresnelReflector(void);
		
		virtual FresnelReflector*
		clone(void) const;

		FresnelReflector&							
		operator= (const FresnelReflector& rhs);
		
		void
		set_eta(const float e);
		
		virtual Color
		f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const;
		
		virtual Color
        sample_f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wr) const;
		
        virtual float
        fresnel(const ShadeRec& sr) const;

		virtual Color
		rho(const ShadeRec& sr, const glm::vec3& wo) const;
				
	private:
	
		float   eta;
};


inline void
FresnelReflector::set_eta(const float e) {
	eta = e;
}
}
