#pragma once

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Phong.h"
#include "PerfectSpecular.h"

namespace Engine{
class Reflective: public Phong {	
	public:
	
		Reflective(void);										

		Reflective(const Reflective& rm);						

		Reflective& 
		operator= (const Reflective& rhs);						

		virtual Reflective*										
		clone(void) const;				

		~Reflective(void);										
		
		void
		set_kr(const float k);
				
		void													
		set_cr(const Color& c);
		
		void
		set_cr(const float r, const float g, const float b);
		
		void
		set_cr(const float c);
		
		virtual Color										
		shade(ShadeRec& s);
		
	private:
	
		PerfectSpecular* reflective_brdf;		
};


// ---------------------------------------------------------------- set_kr

inline void
Reflective::set_kr(const float k) {
	reflective_brdf->set_kr(k);
}


// ---------------------------------------------------------------- set_cr

inline void
Reflective::set_cr(const Color& c) {
	reflective_brdf->set_cr(c);
	
}


// ---------------------------------------------------------------- set_cr

inline void
Reflective::set_cr(const float r, const float g, const float b) {
	reflective_brdf->set_cr(r, g, b);
}


// ---------------------------------------------------------------- set_cr

inline void
Reflective::set_cr(const float c) {
	reflective_brdf->set_cr(c);
}

}
