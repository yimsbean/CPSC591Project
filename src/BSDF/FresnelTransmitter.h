
// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

// this implements perfect specular transmission for transparent materials

#include "BTDF.h"

namespace Engine{
class FresnelTransmitter: public BTDF {
	public:
	
		FresnelTransmitter(void);
		
		FresnelTransmitter(const FresnelTransmitter& ft);
		
		virtual FresnelTransmitter*
		clone(void);
		
		~FresnelTransmitter(void);
		
		FresnelTransmitter&							
		operator= (const FresnelTransmitter& rhs);
		
		void
		set_eta_in(const float ei);
		
		void
		set_eta_out(const float eo);

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
        float   eta_in;
        float   eta_out;
};


// -------------------------------------------------------------- set_kt

inline void
FresnelTransmitter::set_eta_in(const float ei) {
	eta_in = ei;
}

// -------------------------------------------------------------- set_ior

inline void
FresnelTransmitter::set_eta_out(const float eo) {
	eta_out = eo;
}
}