
#include "Bubble.h"

// ---------------------------------------------------------------- default constructor
namespace Engine {
Bubble::Bubble (void)
	:	Phong(),
		fresnel_brdf(new FresnelReflector),
		fresnel_btdf(new FresnelTransmitter)
		//transmittive_brdf(new PerfectTransmitter),
		//reflective_brdf(new PerfectSpecular)
{}



// ---------------------------------------------------------------- copy constructor

Bubble::Bubble(const Bubble& b)
	: 	Phong(b)
{
	/*
	if(b.transmittive_brdf)
		transmittive_brdf = b.transmittive_brdf->clone(); 
	else  
		transmittive_brdf = NULL;

	if(b.reflective_brdf)
		reflective_brdf = b.reflective_brdf->clone(); 
	else  
		reflective_brdf = NULL;	
		*/
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

	/*
	if (transmittive_brdf) {
		delete transmittive_brdf;
		transmittive_brdf = NULL;
	}
	if (reflective_brdf) {
		delete reflective_brdf;
		reflective_brdf = NULL;
	}

	if (rhs.transmittive_brdf)
		transmittive_brdf = rhs.transmittive_brdf->clone();
	if (rhs.reflective_brdf)
		reflective_brdf = rhs.reflective_brdf->clone();
	*/
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
	/*
	if (transmittive_brdf) {
		delete transmittive_brdf;
		transmittive_brdf = NULL;
	}
	if (reflective_brdf) {
		delete reflective_brdf;
		reflective_brdf = NULL;
	}
	*/
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
	Color 		fr = fresnel_brdf->sample_f(sr, wo, wi);  	// computes wi
	Ray 		reflected_ray(sr.hit_point, wi); 
	float 		t;
	Color 		Lr, Lt;
	float 		ndotwi =  glm::dot(sr.normal, wi);
		
	if(fresnel_btdf->tir(sr)) {								// total internal reflection
		if (ndotwi < 0.0) {  	
			// reflected ray is inside
			
			Lr = sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1);
			L += cf_in.powc(t) * Lr;   						// inside filter color
		}
		else {				
			// reflected ray is outside
			
			Lr = sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1);   // kr = 1  
			L += cf_out.powc(t) * Lr;   					// outside filter color
		}
	}
	else { 													// no total internal reflection
		glm::vec3 wt;
		Color ft = fresnel_btdf->sample_f(sr, wo, wt);  	// computes wt
		Ray transmitted_ray(sr.hit_point, wt);
		float ndotwt = glm::dot(sr.normal,wt);
							
		if (ndotwi < 0.0) {
			// reflected ray is inside
						
			Lr = fr * sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1) * fabs(ndotwi);
			L += cf_in.powc(t) * Lr;     					// inside filter color
				
			// transmitted ray is outside
							
			Lt = ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, t, sr.depth + 1) * fabs(ndotwt); 
			L += cf_out.powc(t) * Lt;   					// outside filter color
		}
		else {				
			// reflected ray is outside

			Lr = fr * sr.w.tracer_ptr->trace_ray(reflected_ray, t, sr.depth + 1) * fabs(ndotwi); 
			L += cf_out.powc(t) * Lr;						// outside filter color
				
			// transmitted ray is inside
			
			Lt = ft * sr.w.tracer_ptr->trace_ray(transmitted_ray, t, sr.depth + 1) * fabs(ndotwt); 
			L += cf_in.powc(t) * Lt; 						// inside filter color
		}		
	}	
	return (L);
}

}