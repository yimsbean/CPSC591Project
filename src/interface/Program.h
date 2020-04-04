#pragma once

#include <iostream>
#include <string>

#include "Constants.h"
#include "World.h"
struct GLFWwindow;

namespace Engine{
//process I/O related things
class Program {
	public:
		bool		isShiftPressed = false;
		bool		isMousePressed = false;
		bool		isDrawingFinished = true;
		glm::vec2	mouseLocation = glm::vec2(0.f);
		
		Program();
		virtual ~Program();

		//Creates the rendering engine and the scene and does the main draw loop
		void 
		start();

		World* 
		getWorld() { return world; }

		void 
		reload();
	private:
		GLFWwindow* window = nullptr;
		World* world = nullptr;

		//ImageBuffer image;
		//Intersections intersect;
		//Loader load;
		//Initializes GLFW and creates the window
		void 
		setupWindow();

		void 
		QueryGLVersion();
		
		void 
		destroyWindow();
};

//Functions passed to GLFW to handle errors and keyboard input
//Note, GLFW requires them to not be member functions of a class
void 
ErrorCallback(int error, const char* description);

void 
KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

void 
MouseCallback(GLFWwindow* window,int button, int action, int mods);

void 
MousePositionCallback(GLFWwindow* window,double xpos,double ypos);

void 
MouseScrollCallback(GLFWwindow* window,double xoffset,double yoffset);
}