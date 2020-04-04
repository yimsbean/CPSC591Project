#pragma once

#include "Constants.h"

class Ray {
	public:
	
		glm::vec3			o;  	// origin 
		glm::vec3			d; 		// direction 
		

		Ray();			
		
		Ray(const glm::vec3& origin, const glm::vec3& dir);	
		
		Ray(const Ray& ray); 		
		
		Ray& 						
		operator= (const Ray& rhs);
		 								
		~Ray();

};
