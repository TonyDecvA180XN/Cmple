#ifndef CMPLE_ENGINE_H_INCLUDED
#define CMPLE_ENGINE_H_INCLUDED

#include <iostream>

#include "GL\glm\ext.hpp"
#include "GL\glad.h"
#include "GL\glfw3.h"
#include "stb_image.h"
#include "shader.h"
#include "camera.h"
#include "sprite.h"
#include "model.h"
#include "sound.h"
#include "classes_implementation.h"

extern Camera camera;
extern Shader shader_default_3d;

extern const unsigned int SCR_WIDTH;
extern const unsigned int SCR_HEIGHT;

#include "classes_implementation.h"

void processInput(GLFWwindow *window);

void reshape(GLFWwindow *window, int width, int height);

void update();

void render();

void LoadResources();

void start();

#endif // CMPLE_ENGINE_H_INCLUDED
