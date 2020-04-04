#include "Program.h"

namespace Engine{
//#Program =========
//Constructor
Program::Program() 
{ setupWindow(); }
//Destructor
Program::~Program() 
{ destroyWindow(); }

//public ---------
//MAIN WHILE LOOP
void 
Program::start() {
	//Main render loop
	while(!glfwWindowShouldClose(window)) {
		//world->draw();
		glfwSwapBuffers(window);
		//glfwPollEvents();
		glfwWaitEvents();
		glfwWaitEventsTimeout(1);
	}
}
//private ---------
// called when created
void 
Program::setupWindow() {
	//Initialize the GLFW windowing system
	if (!glfwInit()) {
		std::cout << "ERROR: GLFW failed to initialize, TERMINATING" << std::endl;
		return;
	}

	//Set the custom error callback function
	//Errors will be printed to the console
	glfwSetErrorCallback(&ErrorCallback);

	//Attempt to create a window with an OpenGL 4.6 core profile context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	int width = 960;
	int height = 540;
	window = glfwCreateWindow(width, height, "CPSC 591 Project", 0, 0);
	if (!window) {
		std::cout << "Program failed to create GLFW window, TERMINATING" << std::endl;
		glfwTerminate();
		return;
	}
	glfwSetWindowUserPointer(window, this);
	//Set the custom function that tracks key presses
	glfwSetKeyCallback(window, &KeyCallback);
	glfwSetMouseButtonCallback(window, &MouseCallback);
	glfwSetCursorPosCallback(window, &MousePositionCallback);
	glfwSetScrollCallback(window, &MouseScrollCallback);

	//Bring the new window to the foreground (not strictly necessary but convenient)
	glfwMakeContextCurrent(window);

	//Intialize GLAD (finds appropriate OpenGL configuration for your system)
	if (!gladLoadGL()) {
		std::cout << "GLAD init failed" << std::endl;
		return;
	}

	//Query and print out information about our OpenGL environment
	QueryGLVersion();

	//-----------------------------------
	// create world
	world = new World(width,height);
}
//msg - gl version
void 
Program::QueryGLVersion() {
	// query opengl version and renderer information
	std::string version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
	std::string glslver = reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));
	std::string renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));

	std::cout << "OpenGL [ " << version << " ] "
		<< "with GLSL [ " << glslver << " ] "
		<< "on renderer [ " << renderer << " ]" << std::endl;
}
//msg - error
void 
ErrorCallback(int error, const char* description) {
	std::cout << "GLFW ERROR " << error << ":" << std::endl;
	std::cout << description << std::endl;
}
//I/O - keyboard
void 
KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if(action == GLFW_PRESS){
		Program * program = (Program*)glfwGetWindowUserPointer(window);
		//ESC / scenechange
		switch(key){
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, GL_TRUE); 
				return;
			case GLFW_KEY_1:
				(program->getWorld())->loadScene(1);
				return;
			case GLFW_KEY_2:
				(program->getWorld())->loadScene(2);
				return;
			case GLFW_KEY_3:
				(program->getWorld())->loadScene(3);
				return;
			case GLFW_KEY_LEFT_SHIFT:
				program->isShiftPressed = true;
				return;
		}
		//camera movement
		float DEGREE = 5.f;
		auto& camera = (program->getWorld())->camera;
		switch(key){
			//moving "normal"
			case GLFW_KEY_Q:
				camera.add_roll(-DEGREE);break;
			case GLFW_KEY_E:
				camera.add_roll(DEGREE);break;

			//moving "lookat", world coordiate
			case GLFW_KEY_W:
				camera.add_pitch(DEGREE);break;
			case GLFW_KEY_S:
				camera.add_pitch(-DEGREE);break;
			//moving "normal"
			case GLFW_KEY_A:
				camera.add_yaw(-DEGREE);break;
			case GLFW_KEY_D:
				camera.add_yaw(DEGREE);break;
			
			//moving "eye" on the surface of "view" sphere
			case GLFW_KEY_UP:
				camera.add_camera(0.f, -DEGREE);break;
			case GLFW_KEY_DOWN:
				camera.add_camera(0.f, DEGREE);break;
			case GLFW_KEY_LEFT:
				camera.add_camera(DEGREE, 0.f);break;
			case GLFW_KEY_RIGHT:
				camera.add_camera(-DEGREE, 0.f);break;
				//zooming in/out "view" sphere
			case GLFW_KEY_PAGE_UP:
				camera.add_zoom(-DEGREE);break;
			case GLFW_KEY_PAGE_DOWN:
				camera.add_zoom(DEGREE);break;

				//move forward
			case GLFW_KEY_SPACE:
				camera.move(-DEGREE);break;

			case GLFW_KEY_R:
				camera.reset();break;
			default:	return;
		}
		if(DEBUG_CAMERA){
		std::cout<<
			"CAMERA EYE = [" <<camera.get_eye().x <<", " <<camera.get_eye().y <<", " <<camera.get_eye().z <<"] " <<
			" LOOK = [" <<camera.get_lookat().x <<", " <<camera.get_lookat().y <<", " <<camera.get_lookat().z <<"] " <<
			" UP = [" <<camera.get_up().x <<", " <<camera.get_up().y <<", " <<camera.get_up().z <<"] " <<
			" FOV = [" <<camera.get_fov() <<"]\n";
		}
		program->getWorld()->update();
	}else if(action == GLFW_RELEASE){
		if(key == GLFW_KEY_LEFT_SHIFT){
			Program * program = (Program*)glfwGetWindowUserPointer(window);
			program->isShiftPressed = false;
			return;
		}
	}
}
/**
 * Checks if mouse is pressed or not.
 * If mouse is pressed, record mouse coordinates.
 */
void 
MouseCallback(GLFWwindow* window,int button, int action, int mods) {
	//for dragging
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		Program * program = (Program*)glfwGetWindowUserPointer(window);
        switch (action) {
            case GLFW_PRESS:
                program->isMousePressed = true;
                break;
            case GLFW_RELEASE:
                program->isMousePressed = false;
                break;
        }
    }
}
/**
 * Cursor position for dragging.
 */
void 
MousePositionCallback(GLFWwindow* window,double xpos,double ypos) {
	Program * program = (Program*)glfwGetWindowUserPointer(window);
	if(program->isMousePressed){
		auto& camera = (program->getWorld())->camera;
		camera.add_camera(
			program->mouseLocation.x - xpos, 
			program->mouseLocation.y - ypos
		);
		program->getWorld()->update();
	}
	program->mouseLocation = glm::vec2((float)xpos, (float)ypos);
}
/**
 * Scrolling zooms in and out
 */
void 
MouseScrollCallback(GLFWwindow* window,double xoffset,double yoffset) {
	Program * program = (Program*)glfwGetWindowUserPointer(window);
	auto& camera = (program->getWorld())->camera;
	//if shift pressed + scrolled ==> change fov
	if(program->isShiftPressed){
		camera.add_fov(yoffset);
	}else{
		camera.add_zoom(yoffset);
	}
	program->getWorld()->update();
}


void 
Program::destroyWindow() {
	if(world != nullptr){
		delete world;
		world = nullptr;
	}
	if(window != nullptr){
		glfwDestroyWindow(window);
		//if(window != nullptr){
		//	delete window;
		//	window = nullptr;
		//}
	}
}



}