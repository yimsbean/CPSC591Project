#pragma once
// BRDF base

#include <cmath>

#include "Constants.h"
#include "ShadeRec.h"
#include "Color.h"

namespace Engine{
//bidirectional reflectance distribution function
class BRDF {
	public:
	//@variables

	//@basics(constructor, desturctor, ...)
		BRDF();						
		BRDF(const BRDF& object);
		virtual ~BRDF();

		virtual BRDF* 
		clone() const = 0;

	//@functions
		virtual Color
		f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const;

		virtual Color
		rho(const ShadeRec& sr, const glm::vec3& wo) const;
		
	protected:
	//@variables

	//@basics(constructor, desturctor, ...)
		BRDF&
		operator= (const BRDF& rhs);
	//@functions
};
}
