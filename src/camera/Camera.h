#pragma once
// Camera base
#include "Constants.h"

namespace Engine{
class Camera {
	public:
	//@variables

	//@basics(constructor, desturctor, ...)
		Camera();   							// default constructor
		Camera(const Camera& c);			// copy constructor
		virtual ~Camera(); 

		Camera& 				
		operator= (const Camera& rhs);	

		virtual Camera*
		clone() const;
		
	//@functions
		glm::vec3&
		get_eye();

		glm::vec3&
		get_lookat();

		glm::vec3&
		get_up();

		float
		get_fov();

		glm::vec3&
		get_u();

		glm::vec3&
		get_v();

		glm::vec3&
		get_w();

		glm::vec3
		get_direction(glm::vec2 in);
		//@for quick moving + reset()
		void
		set_eye(const glm::vec3& p);
		void
		set_eye(const float x, const float y, const float z);
		
		void
		set_lookat(const glm::vec3& p);
		void
		set_lookat(const float x, const float y, const float z);

		void
		set_up(const glm::vec3& u);
		void
		set_up(const float x, const float y, const float z);

		void
		set_fov(const float f);

		//reset back to initial value
		void
		reset();

		//moving "lookat", world coordiate
		void
		add_pitch(const float deg);

		void
		add_yaw(const float deg);

		//moving "normal"
		void
		add_roll(const float deg);
		

		//moving "eye" on the surface of "view" sphere
		void
		add_camera(const float x, const float y);
		//moving "lookat"
		void
		move_camera(const float x, const float y);
		void
		add_zoom(const float deg);

		//move forward
		void
		move(const float deg);

		void
		add_fov(const float deg);

		void
		recalcUVW();
	private:		
	//@variables
		glm::vec3			eye;				// eye point
		glm::vec3			lookat; 			// lookat point
		glm::vec3			up;					// up vector
		float				fov;

		//prevent re-calculation of resource-heavy calculations(normalize)
		//used in recalcUVW and get_direction
		glm::vec3			u;					// xcoord in screen
		glm::vec3			v; 					// ycoord in screen
		glm::vec3			w;					// depth
	
		glm::vec3			init_eye;				// eye point
		glm::vec3			init_lookat; 			// lookat point
		glm::vec3			init_up;					// up vector
		float				init_fov;
	//@basics(constructor, desturctor, ...)

	//@functions
		void
		save_init_values();
		
		void 
		recalc_up();

};
inline glm::vec3&
Camera::get_eye() {
	return eye;
}
inline glm::vec3&
Camera::get_lookat() {
	return lookat;
}
inline glm::vec3&
Camera::get_up() {
	return up;
}
inline float
Camera::get_fov() {
	return fov;
}
inline glm::vec3&
Camera::get_u() {
	return u;
}
inline glm::vec3&
Camera::get_v() {
	return v;
}
inline glm::vec3&
Camera::get_w() {
	return w;
}

// ----------------------------------------------------------------- set_eye
inline void
Camera::set_eye(const glm::vec3& p) {
	eye = p;
	save_init_values();
}
inline void
Camera::set_eye(const float x, const float y, const float z) {
	eye.x = x; eye.y = y; eye.z = z;
	save_init_values();
}


// ----------------------------------------------------------------- set_lookat
inline void
Camera::set_lookat(const glm::vec3& p) {
	lookat = p;
	save_init_values();
}
inline void
Camera::set_lookat(const float x, const float y, const float z) {
	lookat.x = x; lookat.y = y; lookat.z = z;
	save_init_values();
}


// ----------------------------------------------------------------- set_up_vector
inline void
Camera::set_up(const glm::vec3& u) {
	up = u;
	save_init_values();
}
inline void
Camera::set_up(const float x, const float y, const float z) {
	up.x = x; up.y = y; up.z = z;
	save_init_values();
}

// ----------------------------------------------------------------- set_fov
inline void
Camera::set_fov(const float f) {
	fov = f;
	save_init_values();
}


}