#pragma once
//minimal include

//**Must include glad and GLFW in this order or it breaks**
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


//just in case for including cmath, for M_PI value
#define _USE_MATH_DEF

#define EPSILON 0.000001

#include <iostream>
#define DEBUG_TEXTURE false
#define DEBUG_CAMERA false
#define DEBUG_RENDER_COLOR false
#define DEBUG_TIME true
//#define DEBUG true
