#include "Camera.h"

namespace Engine{
//#Lambertian =========
//public ------
//@basics(constructor, desturctor, ...)

//constructor
Camera::Camera():
	eye(glm::vec3(1.f,1.f,1.f)),
	lookat(glm::vec3(0.f,0.f,0.f)),
	up(glm::vec3(0.f,1.f,0.f)),
	fov(M_PI/4)
{recalc_up();save_init_values();}
Camera::Camera(const Camera& c):
	eye(c.eye),
	lookat(c.lookat),
	up(c.up),
	fov(c.fov)
{save_init_values();}

//destructor
Camera::~Camera() 
{}

//operator(=)
Camera& 
Camera::operator= (const Camera& rhs) {
	if (this == &rhs) return (*this);
	eye				= rhs.eye;
	lookat			= rhs.lookat;
	up				= rhs.up;
	fov			 	= rhs.fov;
	return (*this);
}

Camera* 
Camera::clone(void) const {
	return (new Camera(*this));
}

//@functions

//reset back to initial value
void
Camera::reset(){
	eye = init_eye;
	lookat = init_lookat;
	up = init_up;
	fov = init_fov;
	recalc_up();
	save_init_values();
}
void
Camera::save_init_values(){
	init_eye = eye;
	init_lookat = lookat;
	init_up = up;
	init_fov = fov;
}
glm::vec3
Camera::get_direction(glm::vec2 in) {
	//float distance = glm::distance(lookat,eye);
	glm::vec3 w = glm::normalize(eye - lookat);
	glm::vec3 u = glm::cross(glm::normalize(up),w);
	glm::vec3 v = glm::cross(w,u);

	return glm::normalize(in.x * u + in.y * v - 2000.f * fov/(float)M_PI * w);
}
void
Camera::recalc_up(){
	//assume upvec was normlized
	glm::vec3 lookvec;
	if(lookat != eye)
		lookvec = glm::normalize(eye - lookat);
	else	
		lookvec = glm::normalize(glm::vec3(1.f,0.f,1.f));
	up = glm::cross(glm::cross(lookvec, up),lookvec);
}
//moving "lookat, eye", world coordiate
//key : WS
void
Camera::add_pitch(const float deg){
	auto degree = deg/4 * up;
	lookat += degree; eye += degree;
}
//key : AD
void
Camera::add_yaw(const float deg){
	auto right = glm::normalize(glm::cross((eye - lookat),up));
	auto degree = deg/4 * right;
	lookat += degree; eye += degree;
}
//moving "normal"
//key : QE
void
Camera::add_roll(const float deg){
	//NORMAL rotating around VIEWVECTOR
	up = glm::rotate(glm::mat4(1.f),glm::radians(4*deg), glm::normalize(eye - lookat)) * glm::vec4(up,1.f);
}


//moving "eye" on the surface of "view" sphere
//key : UP/DOWN/LEFT/RIGHT
void
Camera::add_camera(const float x, const float y){
	//if x == 0, VIEWVECTOR, NORMAL rotating around cross(VIEWVECTOR,NORMAL)
	//if y == 0, VIEWVECTOR 		rotating around NORMAL
	//else => ALL MOVING
	float distance = glm::distance(lookat,eye);
	glm::vec3 viewVec = glm::normalize(eye - lookat);
	glm::vec3 cross = glm::cross(viewVec,up);
	glm::mat4 mat(1.f);
	//+x == moving FROM viewvector TOWARDS cross, axis is up
	mat = glm::rotate(mat,glm::radians(x),up);
	//+y == moving FROM viewvector TOWARDS normal, axis is cross
	mat = glm::rotate(mat,glm::radians(y),cross);

	up = mat * glm::vec4(up,1.f);
	viewVec = mat * glm::vec4(viewVec,1.f);
	eye = lookat + distance*viewVec;
}

//key : PGUP/PGDN
void
Camera::add_zoom(const float deg){
	eye = lookat + (1 + deg/45) * (eye - lookat);
}

//key : space
void
Camera::move(const float deg){
	float distance = glm::distance(lookat,eye);
	glm::vec3 viewVec = glm::normalize(eye - lookat);

	lookat = lookat - (deg/50) * (eye - lookat);
	eye = lookat + distance*viewVec;
}

void
Camera::add_fov(const float deg){
	auto degree = fov + deg*M_PI/720;
	//0~180 deg
	if(!(degree > M_PI/2 &&degree < 0))
	fov = degree;
}



}