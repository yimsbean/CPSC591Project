#pragma once

#include "World.h"			// required for the shade function in all derived classes
#include "Color.h"
#include "ShadeRec.h"

namespace Engine{
class Material {	
	public:
	
		Material(void);						
		
		Material(const Material& material); 
		
		virtual Material*								
		clone(void) const = 0;	
				
		virtual 								
		~Material(void);
				
		virtual Color
		shade(ShadeRec& sr);
		
	protected:
		Material& 								
		operator= (const Material& rhs);						
};
}
