#pragma once

#include "Color.h"
#include "Ray.h"

namespace Engine {
class ShadeRec;
//-------------------------------------------------------------------- class Light

class Light {	
	public:
	
		Light(void);
								
		Light(const Light& ls);			

		Light& 								
		operator= (const Light& rhs); 

		virtual Light*
		clone(void) const = 0;
		
		virtual 							
		~Light(void);
						
		virtual glm::vec3								
		get_direction(ShadeRec& sr) = 0;				
																
		virtual Color														
		L(ShadeRec& sr);								
};
}