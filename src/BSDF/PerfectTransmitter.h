// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.

#pragma once

// this implements perfect specular transmission for transparent materials

#include "BTDF.h"

namespace Engine{
class PerfectTransmitter: public BTDF {
	public:
	
		PerfectTransmitter(void);
		
		PerfectTransmitter(const PerfectTransmitter& pt);
		
		virtual PerfectTransmitter*
		clone(void);
		
		~PerfectTransmitter(void);
		
		PerfectTransmitter&							
		operator= (const PerfectTransmitter& rhs);
		
		void
		set_kt(const float k);
		
		void
		set_ior(const float eta);

		bool													
		tir(const ShadeRec& sr) const;
		
		virtual Color
		f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const;
		
		virtual Color
		sample_f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wt) const;
		
		virtual Color
		rho(const ShadeRec& sr, const glm::vec3& wo) const;
				
	private:
	
		float	kt;			// transmission coefficient
		float	ior;		// index of refraction
};


// -------------------------------------------------------------- set_kt

inline void
PerfectTransmitter::set_kt(const float k) {
	kt = k;
}

// -------------------------------------------------------------- set_ior

inline void
PerfectTransmitter::set_ior(const float eta) {
	ior = eta;
}
}