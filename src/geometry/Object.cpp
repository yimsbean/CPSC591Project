#include "Object.h"

namespace Engine{
// ---------------------------------------------------------------------- default constructor

Object::Object(void)
	: 	color(black),
		material_ptr(NULL)
{}


// ---------------------------------------------------------------------- copy constructor

Object::Object (const Object& object)
	: 	color(object.color) {
	if(object.material_ptr)
		material_ptr = object.material_ptr->clone(); 
	else  
		material_ptr = NULL;
}	


// ---------------------------------------------------------------------- assignment operator

Object&														
Object::operator= (const Object& rhs) {
	if (this == &rhs)
		return (*this);
		
	color = rhs.color;
	
	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}

	if (rhs.material_ptr)
		material_ptr = rhs.material_ptr->clone();

	return (*this);
}


// ---------------------------------------------------------------------- destructor

Object::~Object (void) {	
	if (material_ptr) {
		delete material_ptr;
		material_ptr = NULL;
	}
}


// ----------------------------------------------------------------------- set_material

void 
Object::set_material(Material* mPtr) {
	material_ptr = mPtr;
}


// ----------------------------------------------------------------------- get_material

Material* 
Object::get_material(void) const {
	return (material_ptr);
}						

void
Object::set_color(const Color& c){
	color = c;
}
void
Object::set_color(const float r, const float g, const float b){
	color = Color(r,g,b);
}

}