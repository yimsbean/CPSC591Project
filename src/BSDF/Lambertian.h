#pragma once
//Lambertian

#include "BRDF.h"

namespace Engine{
//REQUIRED FOR all "type-not-specified(default)" MATERIALS
class Lambertian: public BRDF {
	public:
	//@variables

	//@basics(constructor, desturctor, ...)
		Lambertian();
		Lambertian(const Lambertian& lamb);
		~Lambertian();

		virtual Lambertian* 
		clone(void) const;
		
	//@functions
		virtual Color
		f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const;
		
		virtual Color
		rho(const ShadeRec& sr, const glm::vec3& wo) const;
			
		void
		set_ka(const float ka);	
				
		void
		set_kd(const float kd);
		
		void
		set_cd(const Color& c);
		void													
		set_cd(const float r, const float g, const float b);
		void													
		set_cd(const float c);
					
	private:
	//@variables
		float kd;
		Color cd;
	//@basics(constructor, desturctor, ...)
	//@functions
};




// -------------------------------------------------------------- set_ka

inline void
Lambertian::set_ka(const float k) {
	kd = k;
}



// -------------------------------------------------------------- set_kd

inline void
Lambertian::set_kd(const float k) {
	kd = k;
}


// -------------------------------------------------------------- set_cd

inline void
Lambertian::set_cd(const Color& c) {
	cd = c;
}


// ---------------------------------------------------------------- set_cd

inline void													
Lambertian::set_cd(const float r, const float g, const float b) {
	cd.r = r; cd.g = g; cd.b = b;
}


// ---------------------------------------------------------------- set_cd

inline void													
Lambertian::set_cd(const float c) {
	cd.r = c; cd.g = c; cd.b = c;
}

}