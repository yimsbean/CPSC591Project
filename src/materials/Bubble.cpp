
#include "Bubble.h"

// ---------------------------------------------------------------- default constructor
namespace Engine {
Bubble::Bubble (void)
	:	Phong(),
		fresnel_brdf(new FresnelReflector),
		fresnel_btdf(new FresnelTransmitter)
{}



// ---------------------------------------------------------------- copy constructor

Bubble::Bubble(const Bubble& b)
	: 	Phong(b)
{
	if(b.fresnel_brdf)
		fresnel_brdf = b.fresnel_brdf->clone(); 
	else  
		fresnel_brdf = NULL;

	if(b.fresnel_btdf)
		fresnel_btdf = b.fresnel_btdf->clone(); 
	else  
		fresnel_btdf = NULL;	
}
// ---------------------------------------------------------------- assignment operator

Bubble& 
Bubble::operator= (const Bubble& rhs) {
	if (this == &rhs)
		return (*this);
		
	Phong::operator=(rhs);
	if (fresnel_brdf) {
		delete fresnel_brdf;
		fresnel_brdf = NULL;
	}
	if (fresnel_btdf) {
		delete fresnel_btdf;
		fresnel_btdf = NULL;
	}

	if (rhs.fresnel_brdf)
		fresnel_brdf = rhs.fresnel_brdf->clone();
	if (rhs.fresnel_btdf)
		fresnel_btdf = rhs.fresnel_btdf->clone();
	return (*this);
}

// ---------------------------------------------------------------- clone

Bubble*										
Bubble::clone(void) const {
	return (new Bubble(*this));
}	


// ---------------------------------------------------------------- destructor

Bubble::~Bubble(void) {
	if (fresnel_brdf) {
		delete fresnel_brdf;
		fresnel_brdf = NULL;
	}
	if (fresnel_btdf) {
		delete fresnel_btdf;
		fresnel_btdf = NULL;
	}
}


// ---------------------------------------------------------------- shade

Color
Bubble::shade(ShadeRec& sr) {
	Color L(Phong::shade(sr));
	glm::vec3 	wi;
	glm::vec3 	wo(-sr.ray.d);
	Color fr = fresnel_brdf->sample_f(sr, wo, wi);  	// computes wi
	Ray 		reflected_ray(sr.hit_point, wi); 
	float 		t;
	Color 		Lr, Lt;
	float 		ndotwi =  glm::dot(sr.normal, wi);
		
	if(fresnel_btdf->tir(sr)) {								// total internal reflection
		if (ndotwi < 0.0) {  	
			// reflected ray is inside
			Lr = sr.w.bubble_tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1);
			L += cf.powc(t) * Lr;
		}
		else {
			// reflected ray is outside
			Lr = sr.w.bubble_tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1);   // kr = 1  
			L += cf.powc(t) * Lr;
		}
	}
	else { 													// no total internal reflection
		glm::vec3 wt;
		Color ft = fresnel_btdf->sample_f(sr, wo, wt);  	// computes wt
		Ray transmitted_ray(sr.hit_point, wt);
		float ndotwt = glm::dot(sr.normal,wt);
							
		if (ndotwi < 0.0) {
			// reflected ray is inside			
			Lr = fr * sr.w.bubble_tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1) * fabs(ndotwi);
			L += cf.powc(t) * Lr;
				
			// transmitted ray is outside		
			Lt = ft * sr.w.bubble_tracer_ptr->trace_ray(transmitted_ray, t, sr.depth + 1) * fabs(ndotwt); 
			L += cf.powc(t) * Lt;
			
		}
		else {				
			// reflected ray is outside
			Lr = fr * sr.w.bubble_tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1) * fabs(ndotwi); 
			L += cf.powc(t) * Lr;
				
			// transmitted ray is inside
			Lt = ft * sr.w.bubble_tracer_ptr->trace_ray(transmitted_ray, t, sr.depth + 1) * fabs(ndotwt); 
			L += cf.powc(t) * Lt;
			
		}
	}
	return (L);
}

}