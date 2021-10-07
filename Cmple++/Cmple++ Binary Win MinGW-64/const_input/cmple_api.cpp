#include "cmple_api.h"

bool cmple_api::keyboard[keyboard_key_last + 1];
bool cmple_api::keyboard_pressed[keyboard_key_last + 1];
bool cmple_api::keyboard_pressed_block[keyboard_key_last + 1];
bool cmple_api::keyboard_released[keyboard_key_last + 1];
bool cmple_api::keyboard_released_block[keyboard_key_last + 1];
bool cmple_api::mouse[mouse_key_last + 1];
bool cmple_api::mouse_pressed[mouse_key_last + 1];
bool cmple_api::mouse_pressed_block[mouse_key_last + 1];
bool cmple_api::mouse_released[mouse_key_last + 1];
bool cmple_api::mouse_released_block[mouse_key_last + 1];

void cmple_api::keyboard_update(GLFWwindow* window) {
    for (int key = keyboard_key_first; key <= keyboard_key_last; key++) {
        keyboard_pressed[key] = false;
        keyboard_released[key] = false;
    }
    for (int key = keyboard_key_first; key <= keyboard_key_last; key++) {
        if (glfwGetKey(window, key) == GLFW_PRESS) {
            keyboard[key] = true;
            if (!keyboard_pressed_block[key]) {
                keyboard_pressed[key] = true;
                keyboard_pressed_block[key] = true;
            }
            keyboard_released_block[key] = false;
        }
        if (glfwGetKey(window, key) == GLFW_RELEASE) {
            keyboard[key] = false;
            if (!keyboard_released_block[key]) {
                keyboard_released[key] = true;
                keyboard_released_block[key] = true;
            }
            keyboard_pressed_block[key] = false;
        }
    }
}

void cmple_api::mouse_update(GLFWwindow* window) {
    for (int key = mouse_key_first; key <= mouse_key_last; key++) {
        mouse_pressed[key] = false;
        mouse_released[key] = false;
    }
    for (int key = mouse_key_first; key <= mouse_key_last; key++) {
        if (glfwGetMouseButton(window, key) == GLFW_PRESS) {
            mouse[key] = true;
            if (!mouse_pressed_block[key]) {
                mouse_pressed[key] = true;
                mouse_pressed_block[key] = true;
            }
            mouse_released_block[key] = false;
        }
        if (glfwGetMouseButton(window, key) == GLFW_RELEASE) {
            mouse[key] = false;
            if (!mouse_released_block[key]) {
                mouse_released[key] = true;
                mouse_released_block[key] = true;
            }
            mouse_pressed_block[key] = false;
        }
    }
}

bool keyboard(cmple_keyboard_key key) {
    return cmple_api::keyboard[key];
}

bool keyboard_pressed(cmple_keyboard_key key) {
    return cmple_api::keyboard_pressed[key];
}

bool keyboard_released(cmple_keyboard_key key) {
    return cmple_api::keyboard_released[key];
}

bool mouse(cmple_mouse_button key) {
    return cmple_api::mouse[key];
}

bool mouse_pressed(cmple_mouse_button key) {
    return cmple_api::mouse_pressed[key];
}

bool mouse_released(cmple_mouse_button key) {
    return cmple_api::mouse_released[key];
}

int mouse_x() {
    return cmple_engine::mouse_position_x;
}

int mouse_y() {
    return cmple_engine::mouse_position_y;
}

void set_frame_per_second(double fps) {
    cmple_engine::frame_per_second = fps;
}

void set_resolution(unsigned int width, unsigned int height) {
    cmple_engine::SCR_WIDTH = width;
    cmple_engine::SCR_HEIGHT = height;
}

void set_camera_position(float xPos, float yPos, float zPos,
    float xTarget, float yTarget, float zTarget) {
    cmple_engine::camera_default.SetPositionByLookAt(xPos, yPos, zPos, xTarget, yTarget, zTarget);
}

void set_directional_light_direction(float xDir, float yDir, float zDir) {
    cmple_engine::shader_default_3d.setVec3("dirLight.Position", glm::vec3(xDir, yDir, zDir));
}

void set_directional_light_color(float red, float green, float blue) {
    cmple_engine::shader_default_3d.setVec3("dirLight.Color", glm::vec3(red, green, blue));
}

void set_point_light_position(int index, float xPos, float yPos, float zPos) {
    cmple_engine::shader_default_3d.setVec3("pointLight[" + std::to_string(index) + "].Position", glm::vec3(xPos, yPos, zPos));
}

void set_point_light_color(int index, float red, float green, float blue) {
    cmple_engine::shader_default_3d.setVec3("pointLight[" + std::to_string(index) + "].Color", glm::vec3(red, green, blue));
}

void set_spot_light_position(float xPos, float yPos, float zPos) {
    cmple_engine::shader_default_3d.setVec3("spotLight.Position", glm::vec3(xPos, yPos, zPos));
}

void set_spot_light_color(float red, float green, float blue) {
    cmple_engine::shader_default_3d.setVec3("spotLight.Color", glm::vec3(red, green, blue));
}

void set_spot_light_direction(float red, float green, float blue) {
    cmple_engine::shader_default_3d.setVec3("spotLight.Direction", glm::vec3(red, green, blue));
}

void set_spot_light_angle(float cutOff, float outerCutOff) {
    cmple_engine::shader_default_3d.setFloat("spotLight.CutOff", cos(glm::radians(cutOff)));
    cmple_engine::shader_default_3d.setFloat("spotLight.OuterCutOff", cos(glm::radians(outerCutOff)));
}

void set_exposure(float exposure) {
    cmple_engine::shader_default_3d.setFloat("exposure", exposure);
}

void draw_text(std::string text, cmple_font font, float xPos, float yPos,
    float angleRotate, float xScale, float yScale,
    float colorRed, float colorGreen, float colorBlue) {
    glm::mat4 model_matrix = glm::mat4(1.0f);

    switch (font) {
    case FT_ARIAL:
        cmple_engine::font_default_arial.DrawText(text, xPos, yPos,
            angleRotate, xScale, yScale,
            colorRed, colorGreen, colorBlue,
            cmple_engine::shader_default_text, model_matrix);
        break;

    case FT_CALIBRI:
        cmple_engine::font_default_calibri.DrawText(text, xPos, yPos,
            angleRotate, xScale, yScale,
            colorRed, colorGreen, colorBlue,
            cmple_engine::shader_default_text, model_matrix);
        break;

    case FT_TIMES_NEW_ROMAN:
        cmple_engine::font_default_times_new_roman.DrawText(text, xPos, yPos,
            angleRotate, xScale, yScale,
            colorRed, colorGreen, colorBlue,
            cmple_engine::shader_default_text, model_matrix);
        break;
    }
}

void draw_sprite(Sprite sprite, float xPos, float yPos,
    float angleRotate, float xScale, float yScale,
    float colorRed, float colorGreen, float colorBlue) {
    glm::mat4 model_matrix = glm::mat4(1.0f);
    sprite.Draw(xPos, yPos, angleRotate, xScale, yScale, colorRed, colorGreen, colorBlue, cmple_engine::shader_default_2d, model_matrix);
}

void draw_model(Model model, float xPos, float yPos, float zPos,
    float angleRotate, float xRotate, float yRotate, float zRotate,
    float xScale, float yScale, float zScale) {
    glm::mat4 model_matrix = glm::mat4(1.0f);
    model.Draw(xPos, yPos, zPos, angleRotate, xRotate, yRotate, zRotate, xScale, yScale, zScale, cmple_engine::shader_default_3d, model_matrix);
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
