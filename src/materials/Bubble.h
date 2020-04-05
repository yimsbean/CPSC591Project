#pragma once

#include "Phong.h"
#include "PerfectTransmitter.h"
#include "PerfectSpecular.h"
#include "FresnelTransmitter.h"
#include "FresnelReflector.h"

namespace Engine{
//----------------------------------------------------------------------------- class Bubble

class Bubble: public Phong {	
	public:
			
		Bubble(void);										

		Bubble(const Bubble& rm);						

		Bubble& 
		operator= (const Bubble& rhs);						

		virtual Bubble*										
		clone(void) const;				

		~Bubble(void);	

		/*
		void
		set_kt(const float k);

		void
		set_ior(const float ior);
				
		void
		set_kr(const float k);
				
		void													
		set_cr(const Color& c);
		
		void
		set_cr(const float r, const float g, const float b);
		
		void
		set_cr(const float c);
		*/
		void
		set_cf_in(const Color ci);

		void
		set_cf_out(const Color co);

		void
		set_eta_in(const float ei);

		void
		set_eta_out(const float eo);

		virtual Color										
		shade(ShadeRec& s);

	private:
		Color 			cf_in;			// interior filter color 
		Color 			cf_out;			// exterior filter color

		FresnelReflector*	fresnel_brdf;
		FresnelTransmitter*	fresnel_btdf;
		//PerfectTransmitter*		transmittive_brdf;
		//PerfectSpecular*		reflective_brdf;
};
inline void
Bubble::set_cf_in(Color ci) {
	cf_in=ci;
}
inline void
Bubble::set_cf_out(Color co) {
	cf_out=co;
}
inline void
Bubble::set_eta_in(const float ei) {
	fresnel_brdf->set_eta_in(ei);
	fresnel_btdf->set_eta_in(ei);
}
inline void
Bubble::set_eta_out(const float eo) {
	fresnel_brdf->set_eta_in(eo);
	fresnel_btdf->set_eta_in(eo);
}
/*
// ---------------------------------------------------------------- set_kr

inline void
Bubble::set_kt(const float k) {
	transmittive_brdf->set_kt(k);
}
inline void
Bubble::set_ior(const float ior) {
	transmittive_brdf->set_ior(ior);
}
// ---------------------------------------------------------------- set_kr

inline void
Bubble::set_kr(const float k) {
	reflective_brdf->set_kr(k);
}


// ---------------------------------------------------------------- set_cr

inline void
Bubble::set_cr(const Color& c) {
	reflective_brdf->set_cr(c);
	
}
inline void
Bubble::set_cr(const float r, const float g, const float b) {
	reflective_brdf->set_cr(r, g, b);
}
inline void
Bubble::set_cr(const float c) {
	reflective_brdf->set_cr(c);
}
*/
}