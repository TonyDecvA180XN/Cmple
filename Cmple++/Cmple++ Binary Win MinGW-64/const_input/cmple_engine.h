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
#include "font.h"
#include "classes_implementation.h"

namespace cmple_engine {
    extern double frame_per_second;

    extern int mouse_position_x;
    extern int mouse_position_y;

    extern Camera camera_default;

    extern Shader shader_default_3d;
    extern Shader shader_default_2d;
    extern Shader shader_default_text;

    extern Font font_default_arial;
    extern Font font_default_calibri;
    extern Font font_default_times_new_roman;

    extern unsigned int SCR_WIDTH;
    extern unsigned int SCR_HEIGHT;

    void processInput(GLFWwindow* window);

    void reshape(GLFWwindow* window, int width, int height);

    void update();

    void render();

    void load_resources();

    void start();
}

#endif // CMPLE_ENGINE_H_INCLUDED
