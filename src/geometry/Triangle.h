#pragma once
#include "Object.h"

namespace Engine{
	
class Triangle: public Object {		
	public:
	//@variables

    //@basics(constructor, desturctor, ...)
		Triangle();   									
		Triangle(const Triangle& tr);
		Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3);		
		virtual ~Triangle();   			

		virtual Triangle* 
		clone() const;	//allow clone			

		Triangle& 
		operator= (const Triangle& tr);
	//@functions
		virtual void
		set_color(const Color& c);
		virtual void
		set_color(const float r, const float g, const float b);

		virtual	bool 
		hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

		//virtual bool 
		//shadow_hit(const Ray& ray, double& tmin) const;

	private:
	//@variables
		glm::vec3   p1, p2, p3;
        glm::vec3   normal;
	//@basics(constructor, desturctor, ...)

	//@functions
		void
		calculate_normal();
};

}
