#include "Program.h"
#include <mutex>

//initialization of extern variables defined in Constants.h
bool DEBUG_RADIANCE_TEXTURE=false;
bool DEBUG_CUBEMAP_TEXTURE=false;
bool RENDER_OLD_METHOD=false;
bool OPTIMIZED_METHOD=true;
int LIGHT_TEXTURE_METHOD = 0;


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
		// PINHOLE CAMERA!
	auto& camera = world->camera;
	while(!glfwWindowShouldClose(window)) {
		//world->draw();
		//glfwSwapBuffers(window);

		glfwWaitEventsTimeout(1);
		//glfwPollEvents();

		//camera.add_camera(2.f, 0.f);
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

	//Attempt to create a window with an OpenGL 3.3 core profile context
	//GLFW_MAJOR_VERSION, GLFW_MINOR_VERSION defined in utilities/Constants.h
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW_MAJOR_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_MINOR_VERSION);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	int width = 400;
	int height = 400;
	window = glfwCreateWindow(width, height, "CPSC 591 Project", 0, 0);
	if (!window) {
		std::cout << "Program failed to create GLFW window, TERMINATING" << std::endl;
		glfwTerminate();
		return;
	}
	glfwSetWindowUserPointer(window, this);
	//Set the custom function that tracks key presses
	glfwSetKeyCallback(window, &KeyCallback);
	//glfwSetMouseButtonCallback(window, &MouseCallback);
	//glfwSetCursorPosCallback(window, &MousePositionCallback);
	//glfwSetScrollCallback(window, &MouseScrollCallback);

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
	//initial swap buffering
	glfwSwapBuffers(window);
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
		auto* world = program->getWorld();
		//ESC / scenechange
		switch(key){
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, GL_TRUE); 
				return;
			case GLFW_KEY_1:
				DEBUG_RADIANCE_TEXTURE ^= true;
				break;
			case GLFW_KEY_2:
				DEBUG_CUBEMAP_TEXTURE ^= true;
				break;
			case GLFW_KEY_3:
				RENDER_OLD_METHOD ^= true;
				world->loadScene(1);
				break;
			case GLFW_KEY_4:
				OPTIMIZED_METHOD ^= true;
				world->loadScene(1);
				break;
			//light texture
			case GLFW_KEY_F1:
				LIGHT_TEXTURE_METHOD = 0;
				world->generateReflectivityTexture();
				world->loadScene(1);
				break;
			case GLFW_KEY_F2:
				LIGHT_TEXTURE_METHOD = 1;
				world->generateReflectivityTexture();
				world->loadScene(1);
				break;
			case GLFW_KEY_F3:
				LIGHT_TEXTURE_METHOD = 2;
				world->generateReflectivityTexture();
				world->loadScene(1);
				break;
			case GLFW_KEY_F4:
				LIGHT_TEXTURE_METHOD = 3;
				world->generateReflectivityTexture();
				world->loadScene(1);
				break;
			case GLFW_KEY_F5:
				LIGHT_TEXTURE_METHOD = 4;
				world->generateReflectivityTexture();
				world->loadScene(1);
				break;
			//case GLFW_KEY_2:
			//	(program->getWorld())->loadScene(2);
			//	return;
			//case GLFW_KEY_3:
			//	(program->getWorld())->loadScene(3);
			//	return;
			//case GLFW_KEY_LEFT_SHIFT:
			//	program->isShiftPressed = true;
			//	return;
		}
		//camera movement
		float DEGREE = 4.f;
		// PINHOLE CAMERA!
		auto& camera = world->camera;
		switch(key){
			//moving "normal"
			case GLFW_KEY_Q:
				camera.add_roll(DEGREE);break;
			case GLFW_KEY_E:
				camera.add_roll(-DEGREE);break;

			//moving "lookat", world coordiate
			case GLFW_KEY_W:
				camera.add_pitch(DEGREE);break;
			case GLFW_KEY_S:
				camera.add_pitch(-DEGREE);break;
			//moving "normal"
			case GLFW_KEY_A:
				camera.add_yaw(DEGREE);break;
			case GLFW_KEY_D:
				camera.add_yaw(-DEGREE);break;
			//add_camera = moving "eye" on the surface of "view" sphere
			//move_camera = moving "lookat"
			case GLFW_KEY_UP:
				if(mods != GLFW_MOD_SHIFT)
					camera.add_camera(0.f, DEGREE);
				else
					camera.move_camera(0.f, DEGREE);
				break;
			case GLFW_KEY_DOWN:
				if(mods != GLFW_MOD_SHIFT)
					camera.add_camera(0.f, -DEGREE);
				else
					camera.move_camera(0.f, -DEGREE);
				break;
			case GLFW_KEY_LEFT:
				if(mods != GLFW_MOD_SHIFT)
					camera.add_camera(-DEGREE, 0.f);
				else
					camera.move_camera(-DEGREE, 0.f);
				break;
			case GLFW_KEY_RIGHT:
				if(mods != GLFW_MOD_SHIFT)
					camera.add_camera(DEGREE, 0.f);
				else
					camera.move_camera(DEGREE, 0.f);
				break;
				//zooming in/out "view" sphere
			case GLFW_KEY_PAGE_UP:
				camera.add_zoom(-DEGREE);break;
			case GLFW_KEY_PAGE_DOWN:
				camera.add_zoom(DEGREE);break;

				//change fov
			case GLFW_KEY_LEFT_BRACKET:
				camera.add_fov(DEGREE);break;
			case GLFW_KEY_RIGHT_BRACKET:
				camera.add_fov(-DEGREE);break;
				
			//move forward
			case GLFW_KEY_SPACE:
				if(mods != GLFW_MOD_SHIFT)
					camera.move(DEGREE);
				else
					camera.move(-DEGREE);
				break;
			case GLFW_KEY_R:
				camera.reset();
				world->thickness_reset();
				break;
			//------
			//change bubble thickness
			case GLFW_KEY_KP_ADD:
			case GLFW_KEY_EQUAL:
				world->add_bubble_thickness(DEGREE);break;
			case GLFW_KEY_KP_SUBTRACT:
			case GLFW_KEY_MINUS:
				world->add_bubble_thickness(-DEGREE);break;
		}
		if(DEBUG_CAMERA){
			std::cout<<
				"CAMERA EYE = [" <<camera.get_eye().x <<", " <<camera.get_eye().y <<", " <<camera.get_eye().z <<"] " <<
				" LOOK = [" <<camera.get_lookat().x <<", " <<camera.get_lookat().y <<", " <<camera.get_lookat().z <<"] " <<
				" UP = [" <<camera.get_up().x <<", " <<camera.get_up().y <<", " <<camera.get_up().z <<"] " <<
				" FOV = [" <<camera.get_fov() <<"]\n";
		}
		world->update();
		//swap buffer only when updated
		glfwSwapBuffers(window);
	}else if(action == GLFW_RELEASE){
		if(key == GLFW_KEY_LEFT_SHIFT){
			Program * program = (Program*)glfwGetWindowUserPointer(window);
			program->isShiftPressed = false;
			return;
		}
	}
}


//NOT USED
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
//NOT USED
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
//NOT USED
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