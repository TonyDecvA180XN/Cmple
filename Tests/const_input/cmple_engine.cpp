#include "cmple_engine.h"

unsigned int cmple_engine::window_width = 640;
unsigned int cmple_engine::window_height = 480;
std::string cmple_engine::window_name = "Program";
bool cmple_engine::window_close = false;

bool cmple_engine::mutex_display_3d_enabled = false;
bool cmple_engine::mutex_display_2d_enabled = false;

double cmple_engine::frame_per_second = 100.0;

int cmple_engine::mouse_position_x;
int cmple_engine::mouse_position_y;

Camera cmple_engine::camera_default(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);

Shader cmple_engine::shader_default_3d;
Shader cmple_engine::shader_default_2d;
Shader cmple_engine::shader_default_text;

Font cmple_engine::font_default_arial;
Font cmple_engine::font_default_calibri;
Font cmple_engine::font_default_times_new_roman;

void cmple_engine::processInput(GLFWwindow* window) {
    cmple_api::keyboard_update(window);
    cmple_api::mouse_update(window);
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    mouse_position_x = (int)x;
    mouse_position_y = (int)y;
}

void cmple_engine::reshape(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void cmple_engine::update() {
#include "classes_update.h"
}

void cmple_engine::render() {
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glm::mat4 projection = glm::perspective(glm::radians(camera_default.Zoom), (float)window_width / (float)window_height, 0.1f, 100.0f);
        glm::mat4 view = camera_default.GetViewMatrix();
        shader_default_3d.use();
        shader_default_3d.setMat4("projection", projection);
        shader_default_3d.setMat4("view", view);
        shader_default_3d.setVec3("viewPos", camera_default.Position);
    }

    mutex_display_3d_enabled = true;
#include "classes_display_3d.h"
    mutex_display_3d_enabled = false;

    {
        glDisable(GL_DEPTH_TEST);

        glm::mat4 projection = glm::ortho(0.0f, (float)window_width, (float)window_height, 0.0f, -1.0f, 1.0f);
        glm::mat4 model = glm::mat4(1.0f);
        shader_default_2d.use();
        shader_default_2d.setInt("image", 0);
        shader_default_2d.setMat4("projection", projection);
        shader_default_2d.setMat4("model", model);

        shader_default_text.use();
        shader_default_text.setInt("image", 0);
        shader_default_text.setMat4("projection", projection);
        shader_default_text.setMat4("model", model);
    }

    mutex_display_2d_enabled = true;
#include "classes_display_2d.h"
    mutex_display_2d_enabled = false;
}

void cmple_engine::load_resources() {
    shader_default_3d.init("shaders//shader_default_3d.vs", "shaders//shader_default_3d.fs");
    shader_default_2d.init("shaders//shader_default_2d.vs", "shaders//shader_default_2d.fs");
    shader_default_text.init("shaders//shader_default_text.vs", "shaders//shader_default_text.fs");

    font_default_arial.Load("fonts//Arial.fnt");
    font_default_calibri.Load("fonts//Calibri.fnt");
    font_default_times_new_roman.Load("fonts//Times_New_Roman.fnt");
#include "files_load.h"
}

void cmple_engine::start() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

#include "files_audio_load.h"

#include "creation_code.h"


    GLFWwindow* window = glfwCreateWindow(window_width, window_height, window_name.c_str(), NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, reshape);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    load_resources();

    double next_frame_time = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        if (glfwGetTime() < next_frame_time)
            continue;

        next_frame_time += 1.0 / frame_per_second;

        if (glfwGetTime() > next_frame_time)
            next_frame_time = glfwGetTime();

        processInput(window);

        update();
        render();

        if (window_close == true)
            glfwSetWindowShouldClose(window, true);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}
