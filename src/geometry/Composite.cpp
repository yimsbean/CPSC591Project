#include "Composite.h"
#include <algorithm>

namespace Engine{

//#Line =========
//public------
//@basics(constructor, desturctor, ...)

//constructor
Composite::Composite():
    Object()
{}
Composite::Composite(const std::vector<Object*> objects):
    Object(),
    objects(objects)
{}
Composite::Composite(const Composite& comp):
    Object()
{}

//destructor
Composite::~Composite()
{delete_objects();}

Composite* 
Composite::clone() const{
    return (new Composite (*this));
}

//operator(=)
Composite&														
Composite::operator= (const Composite& rhs) {
	if (this == &rhs) return (*this);
    Object::operator=(rhs); objects = std::vector<Object*>(rhs.objects);
	return (*this);
}

//@functions
bool 															 
Composite::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
    for(auto& obj : objects)
        if(obj->hit(ray,tmin,sr))   
            return true;
    return false;
}

//private------
//@functions
void
Composite::set_color(const Color& c){
	color = c;
}
void
Composite::set_color(const float r, const float g, const float b){
	color = Color(r,g,b);
}
void 
Composite::delete_objects(){
    objects.erase(
        std::remove_if(
            objects.begin(),
            objects.end(),
            [](Object* obj) -> bool {
                return true;
            }
        ),
        objects.end()
    );
}
}