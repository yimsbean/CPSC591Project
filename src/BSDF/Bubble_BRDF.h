#pragma once

#include "BRDF.h"
#include "ImageTexture.h"
namespace Engine{
class Bubble_BRDF: public BRDF {
    public:

	Bubble_BRDF(void);

	virtual
	~Bubble_BRDF(void);

	virtual Bubble_BRDF*
	clone(void) const;

    virtual Color
    f(const ShadeRec& sr, const glm::vec3& wo, const glm::vec3& wi) const;

    virtual Color
    rho(const ShadeRec& sr, const glm::vec3& wo) const;

    void
    set_cd(Texture* c);

    private:
    Texture* cd;
};
// -------------------------------------------------------------- set_cd

inline void
Bubble_BRDF::set_cd(Texture* c) {
	cd = c;
}
}