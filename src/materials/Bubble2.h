#pragma once

#include "Material.h"
#include "Texture.h"
#include "Bubble_BRDF.h"
namespace Engine{
class Bubble2: public Material {
    public:

    Bubble2(void);

    Bubble2(const Bubble2& xtoon);

    virtual Material*
    clone(void) const;

    Bubble2&
	operator= (const Bubble2& rhs);

	~Bubble2(void);

    void
	set_cd(Texture* t_ptr);
    
    virtual Color										
	shade(ShadeRec& sr);
    
    Color
    reflectivityShade(ShadeRec& sr);
    
    Color
    textureShade(ShadeRec& sr);
    
    Color
    lighting(ShadeRec& sr);

    private:
	 Bubble_BRDF*		bubble_brdf;
};

// ---------------------------------------------------------------- set_cd

inline void													
Bubble2::set_cd(Texture* t_ptr) {
	bubble_brdf->set_cd(t_ptr);
}
}

