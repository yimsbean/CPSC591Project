#pragma once

#include "Material.h"
#include "Lambertian.h"

namespace Engine{
//----------------------------------------------------------------------------- class Phong

class Phong: public Material {	
	public:
			
		Phong(void);											

		Phong(const Phong& m);
		
		virtual Material*										
		clone(void) const;									

		Phong& 
		operator= (const Phong& rhs);							

		~Phong(void);											
		
		void 													
		set_ka(const float k);
		
		void 													
		set_kd(const float k);
		
		void													
		set_cd(const Color c);
		
		void													
		set_cd(const float r, const float g, const float b);
		
		void																						
		set_cd(const float c);
				
		Color
		shade(ShadeRec& sr);
		
	private:
		
		Lambertian*		ambient_brdf;
		Lambertian*		diffuse_brdf;
};


// ---------------------------------------------------------------- set_ka
// this sets Lambertian::kd
// there is no Lambertian::ka data member because ambient reflection 
// is diffuse reflection

inline void								
Phong::set_ka(const float ka) {
	ambient_brdf->set_kd(ka);
}


// ---------------------------------------------------------------- set_kd
// this also sets Lambertian::kd, but for a different Lambertian object

inline void								
Phong::set_kd (const float kd) {
	diffuse_brdf->set_kd(kd);
}


// ---------------------------------------------------------------- set_cd

inline void												
Phong::set_cd(const Color c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}


// ---------------------------------------------------------------- set_cd

inline void													
Phong::set_cd(const float r, const float g, const float b) {
	ambient_brdf->set_cd(r, g, b);
	diffuse_brdf->set_cd(r, g, b);
}

// ---------------------------------------------------------------- set_cd

inline void													
Phong::set_cd(const float c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}
}