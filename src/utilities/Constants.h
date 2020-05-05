#pragma once
//minimal include

//**Must include glad and GLFW in this order or it breaks**
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


//just in case for including cmath, for M_PI value
#define _USE_MATH_DEF  
#define EPSILON 0.000001
#define GLFW_MAJOR_VERSION 3
#define GLFW_MINOR_VERSION 3
//#include <iostream>

#define DEBUG_CAMERA false
#define DEBUG_TIME true


//Initialization of Extern variables are defined in Program.cpp

//TEXTURE DEBUGGING
//#define DEBUG_RADIANCE_TEXTURE false
//#define DEBUG_CUBEMAP_TEXTURE false

extern bool DEBUG_RADIANCE_TEXTURE;
extern bool DEBUG_CUBEMAP_TEXTURE;

//1. Fresnel ray-tracing(SLOW)
//#define RENDER_OLD_METHOD false
extern bool RENDER_OLD_METHOD;
//2. 3-step divide and conquering problem
//#define OPTIMIZED_METHOD false
extern bool OPTIMIZED_METHOD;

extern int LIGHT_TEXTURE_METHOD;