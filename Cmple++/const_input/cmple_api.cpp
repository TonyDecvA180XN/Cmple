#include "cmple_api.h"

extern Camera camera;
extern Shader shader_default_3d;
extern Shader shader_default_2d;

bool cmple::keyboard[keyboard_key_last + 1];
bool cmple::keyboard_pressed[keyboard_key_last + 1];
bool cmple::keyboard_released[keyboard_key_last + 1];
bool cmple::mouse[mouse_key_last + 1];
bool cmple::mouse_pressed[mouse_key_last + 1];
bool cmple::mouse_released[mouse_key_last + 1];

void cmple::keyboard_update(GLFWwindow *window) {
    for (int key = keyboard_key_first; key <= keyboard_key_last; key++) {
        keyboard_pressed[key] = false;
        keyboard_released[key] = false;
    }
    for (int key = keyboard_key_first; key <= keyboard_key_last; key++) {
        if (glfwGetKey(window, key) == GLFW_PRESS) {
            keyboard[key] = true;
            keyboard_pressed[key] = true;
        }
        if (glfwGetKey(window, key) == GLFW_RELEASE) {
            keyboard[key] = false;
            keyboard_released[key] = true;
        }
    }
}

void cmple::mouse_update(GLFWwindow *window) {
    for (int key = mouse_key_first; key <= mouse_key_last; key++) {
        mouse_pressed[key] = false;
        mouse_released[key] = false;
    }
    for (int key = mouse_key_first; key <= mouse_key_last; key++) {
        if (glfwGetKey(window, key) == GLFW_PRESS) {
            mouse[key] = true;
            mouse_pressed[key] = true;
        }
        if (glfwGetKey(window, key) == GLFW_RELEASE) {
            mouse[key] = false;
            mouse_released[key] = true;
        }
    }
}

bool keyboard(cmple_keyboard_key key) {
    return cmple::keyboard[key];
}

bool keyboard_pressed(cmple_keyboard_key key) {
    return cmple::keyboard_pressed[key];
}

bool keyboard_released(cmple_keyboard_key key) {
    return cmple::keyboard_released[key];
}

bool mouse(cmple_mouse_button key) {
    return cmple::mouse[key];
}

bool mouse_pressed(cmple_mouse_button key) {
    return cmple::mouse_pressed[key];
}

bool mouse_released(cmple_mouse_button key) {
    return cmple::mouse_released[key];
}

void set_camera_position(float xPos, float yPos, float zPos,
                         float xTarget, float yTarget, float zTarget) {
    camera.SetPositionByLookAt(xPos, yPos, zPos, xTarget, yTarget, zTarget);
}

void draw_sprite(Sprite sprite, float xPos, float yPos,
                float angleRotate, float xScale, float yScale,
                float colorRed, float colorGreen, float colorBlue) {
    glm::mat4 model_matrix=glm::mat4(1.0f);
    sprite.Draw(xPos, yPos, angleRotate, xScale, yScale, colorRed, colorGreen, colorBlue, shader_default_2d, model_matrix);
}

void draw_model(Model model, float xPos, float yPos, float zPos,
                float angleRotate, float xRotate, float yRotate, float zRotate,
                float xScale, float yScale, float zScale) {
    glm::mat4 model_matrix=glm::mat4(1.0f);
    model.Draw(xPos, yPos, zPos, angleRotate, xRotate, yRotate, zRotate, xScale, yScale, zScale, shader_default_3d, model_matrix);
}

void sound_play(Sound sound) {
    sound.Play();
}

void sound_stop(Sound sound) {
    sound.Stop();
}

bool sound_is_playing(Sound sound) {
    return sound.IsPlaying();
}
