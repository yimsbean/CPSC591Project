#include "Camera.h"

namespace Engine{
//#Lambertian =========
//public ------
//@basics(constructor, desturctor, ...)

//constructor
Camera::Camera():
	eye(glm::vec3(0.f,0.f,10.f)),
	lookat(glm::vec3(0.f,0.f,-15.f)),
	up(glm::vec3(0.f,1.f, 0.f)),
	fov(M_PI/4)
{recalc_up();}
Camera::Camera(const Camera& c):
	eye(c.eye),
	lookat(c.lookat),
	up(c.up),
	fov(c.fov)
{}

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
	eye = glm::vec3(0.f,0.f,10.f);
	lookat = glm::vec3(0.f,0.f,-15.f);
	up = glm::vec3(0.f,1.f, 0.f);
	fov = M_PI/4;
	recalc_up();
}

void
Camera::recalc_up(){
	//assume upvec was normlized
	glm::vec3 lookvec;
	if(lookat != eye)
		 lookvec = glm::normalize(lookat - eye);
	else	
		lookvec = glm::normalize(glm::vec3(1.f,0.f,1.f));
	up = glm::cross(glm::cross(lookvec, up),lookvec);
}
//moving "lookat, eye", world coordiate
//key : WS
void
Camera::add_pitch(const float deg){
	lookat += deg/20 * up;
	eye += deg/20 * up;
}
//key : AD
void
Camera::add_yaw(const float deg){
	auto right = glm::normalize(glm::cross((lookat - eye),up));
	lookat += deg/20 * right;
	eye += deg/20 * right;
}
//moving "normal"
//key : QE
void
Camera::add_roll(const float deg){
	//NORMAL rotating around VIEWVECTOR
	up = glm::rotate(glm::mat4(1.f),glm::radians(deg), glm::normalize(eye - lookat)) * glm::vec4(up,1.f);
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
	eye = lookat + (1 + deg/180) * (eye - lookat);
}

//key : space
void
Camera::move(const float deg){
	float distance = glm::distance(lookat,eye);
	glm::vec3 viewVec = glm::normalize(eye - lookat);

	lookat = lookat + (deg/100) * (eye - lookat);
	eye = lookat + distance*viewVec;
}

void
Camera::add_fov(const float deg){
	fov += deg;
}



}