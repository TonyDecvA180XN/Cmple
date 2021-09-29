#include "cmple_engine.h"

Camera camera(-2.0f,3.0f,0.0f,0.0f,1.0f,0.0f,0.0f,-60.0f);
Shader shader_default_3d;
Shader shader_default_2d;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void processInput(GLFWwindow *window) {
    cmple::keyboard_update(window);
    cmple::mouse_update(window);
}

void reshape(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void update() {
#include "classes_update.h"
}

void render() {
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        shader_default_3d.use();
        shader_default_3d.setVec3("dirLight.direction", -0.3f, -1.0f, -0.0f);
        shader_default_3d.setVec3("dirLight.ambient", 0.2f, 0.2, 0.2);
        shader_default_3d.setVec3("dirLight.diffuse", 0.7f, 0.7f, 0.7f);
        shader_default_3d.setVec3("dirLight.specular", 0.2f, 0.2f, 0.2f);
        glm::mat4 projection=glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view=camera.GetViewMatrix();
        glm::mat4 model=glm::mat4(1.0f);
        shader_default_3d.setMat4("projection", projection);
        shader_default_3d.setMat4("view", view);
        shader_default_3d.setMat4("model", model);
    }

#include "classes_display_3d.h"

    {
        glDisable(GL_DEPTH_TEST);

        shader_default_2d.use();
        glm::mat4 projection=glm::ortho(0.0f,(float)SCR_WIDTH,(float)SCR_HEIGHT,0.0f,-1.0f,1.0f);
        glm::mat4 model=glm::mat4(1.0f);
        shader_default_2d.setInt("image",0);
        shader_default_2d.setMat4("projection",projection);
        shader_default_2d.setMat4("model",model);
    }

#include "classes_display_2d.h"
}

void LoadResources() {
    shader_default_3d.init("shaders//shader_default_3d.vs","shaders//shader_default_3d.fs");
    shader_default_2d.init("shaders//shader_default_2d.vs","shaders//shader_default_2d.fs");
#include "files_load.h"
}

void start() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Example", NULL, NULL);
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

    LoadResources();

#include "creation_code.h"

    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        update();
        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}
