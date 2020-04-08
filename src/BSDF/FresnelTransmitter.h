
// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

// this implements perfect specular transmission for transparent materials

#include "BTDF.h"

namespace Engine{
//used in bubble(material)
class FresnelTransmitter: public BTDF {
	public:
	
		FresnelTransmitter(void);
		
		FresnelTransmitter(const FresnelTransmitter& ft);
		
		virtual ~FresnelTransmitter(void);

		virtual FresnelTransmitter*
		clone(void);
		
		FresnelTransmitter&							
		operator= (const FresnelTransmitter& rhs);
		
		void
		set_eta(const float e);

		bool													
		tir(const ShadeRec& sr) const;
		
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


// -------------------------------------------------------------- set_kt

inline void
FresnelTransmitter::set_eta(const float e) {
	eta = e;
}

}