#include "Light.h"
#include "Color.h"

#include "ShadeRec.h"

namespace Engine{
class PointLight: public Light {	
	public:
		PointLight(void);   							

		PointLight(const PointLight& pl); 
		
		virtual Light* 									
		clone(void) const;			

		PointLight& 									
		operator= (const PointLight& rhs); 
			
		virtual											
		~PointLight(void); 

        void
		scale_radiance(const float b);

        void
		set_location(glm::vec3 l);						
		
		void
		set_location(float lx, float ly, float lz);

		virtual glm::vec3
		get_direction(ShadeRec& sr);

		virtual Color
		L(ShadeRec& sr);

	private:
		
		float 		ls;
		Color 	    color;
		glm::vec3 	location;
};
inline void
PointLight::scale_radiance(const float b) { 
	ls = b;
}
inline void
PointLight::set_location(glm::vec3 l){
    location = l;
}
inline void
PointLight::set_location(float lx, float ly, float lz){
    location = glm::vec3(lx,ly,lz);
}
}