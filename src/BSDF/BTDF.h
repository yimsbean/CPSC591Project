// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.
#pragma once

#include <math.h>

//#include "Constants.h"
#include "Color.h"
#include "ShadeRec.h"

namespace Engine{
//bidirectional transmittance distribution function
class BTDF {
	public:
	
		BTDF(void);
		
		BTDF(const BTDF& btdf);
		
		virtual BTDF*
		clone(void) = 0;
		
		BTDF&							
		operator= (const BTDF& rhs);
		
		virtual
		~BTDF(void);
				
		virtual Color
		f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const;
		
		virtual Color
		sample_f(const ShadeRec& sr, const glm::vec3& wo, glm::vec3& wt) const;
		
		virtual Color
		rho(const ShadeRec& sr, const glm::vec3& wo) const;
};

}