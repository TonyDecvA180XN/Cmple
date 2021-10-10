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

bool mouse(cmple_mouse_button button) {
    return cmple_api::mouse[button];
}

bool mouse_pressed(cmple_mouse_button button) {
    return cmple_api::mouse_pressed[button];
}

bool mouse_released(cmple_mouse_button button) {
    return cmple_api::mouse_released[button];
}

int mouse_x() {
    return cmple_engine::mouse_position_x;
}

int mouse_y() {
    return cmple_engine::mouse_position_y;
}

void set_resolution(unsigned int width, unsigned int height) {
    cmple_engine::window_width = width;
    cmple_engine::window_height = height;
}

void set_window_name(std::string name) {
    cmple_engine::window_name = name;
}

void set_frame_per_second(double fps) {
    cmple_engine::frame_per_second = fps;
}

void end_program() {
    cmple_engine::window_close = true;
}

void set_camera_position_by_look_at(float posX, float posY, float posZ,
    float targetX, float targetY, float targetZ) {
    cmple_engine::camera_default.SetPositionByLookAt(posX, posY, posZ, targetX, targetY, targetZ);
}

void set_camera_position_by_angles(float posX, float posY, float posZ,
    float upX, float upY, float upZ, float yaw, float pitch) {
    cmple_engine::camera_default.SetPositionByAngles(posX, posY, posZ, upX, upY, upZ, yaw, pitch);
}

void set_exposure(float exposure) {
    if (cmple_engine::mutex_display_3d_enabled) {
        cmple_engine::shader_default_3d.setFloat("exposure", exposure);
    }
}

void set_directional_light_direction(float dirX, float dirY, float dirZ) {
    if (cmple_engine::mutex_display_3d_enabled) {
        cmple_engine::shader_default_3d.setVec3("dirLight.Position", glm::vec3(dirX, dirY, dirZ));
    }
}

void set_directional_light_color(float colorRed, float colorGreen, float colorBlue) {
    if (cmple_engine::mutex_display_3d_enabled) {
        cmple_engine::shader_default_3d.setVec3("dirLight.Color", glm::vec3(colorRed, colorGreen, colorBlue));
    }
}

void set_point_light_position(int index, float posX, float posY, float posZ) {
    if (cmple_engine::mutex_display_3d_enabled) {
        cmple_engine::shader_default_3d.setVec3("pointLight[" + std::to_string(index) + "].Position", glm::vec3(posX, posY, posZ));
    }
}

void set_point_light_color(int index, float colorRed, float colorGreen, float colorBlue) {
    if (cmple_engine::mutex_display_3d_enabled) {
        cmple_engine::shader_default_3d.setVec3("pointLight[" + std::to_string(index) + "].Color", glm::vec3(colorRed, colorGreen, colorBlue));
    }
}

void set_spot_light_position(float posX, float posY, float posZ) {
    if (cmple_engine::mutex_display_3d_enabled) {
        cmple_engine::shader_default_3d.setVec3("spotLight.Position", glm::vec3(posX, posY, posZ));
    }
}

void set_spot_light_color(float colorRed, float colorGreen, float colorBlue) {
    if (cmple_engine::mutex_display_3d_enabled) {
        cmple_engine::shader_default_3d.setVec3("spotLight.Color", glm::vec3(colorRed, colorGreen, colorBlue));
    }
}

void set_spot_light_direction(float dirX, float dirY, float dirZ) {
    if (cmple_engine::mutex_display_3d_enabled) {
        cmple_engine::shader_default_3d.setVec3("spotLight.Direction", glm::vec3(dirX, dirY, dirZ));
    }
}

void set_spot_light_angle(float angleInner, float angleOuter) {
    if (cmple_engine::mutex_display_3d_enabled) {
        cmple_engine::shader_default_3d.setFloat("spotLight.angleInner", cos(glm::radians(angleInner)));
        cmple_engine::shader_default_3d.setFloat("spotLight.angleOuter", cos(glm::radians(angleOuter)));
    }
}

void draw_text(std::string text, cmple_font font, float posX, float posY,
    float rotateAngle, float scaleX, float sizeY,
    float colorRed, float colorGreen, float colorBlue) {

    if (cmple_engine::mutex_display_2d_enabled) {
        glm::mat4 model_matrix = glm::mat4(1.0f);

        switch (font) {
        case FT_ARIAL:
            cmple_engine::font_default_arial.DrawText(text, posX, posY,
                rotateAngle, scaleX, sizeY,
                colorRed, colorGreen, colorBlue,
                cmple_engine::shader_default_text, model_matrix);
            break;

        case FT_CALIBRI:
            cmple_engine::font_default_calibri.DrawText(text, posX, posY,
                rotateAngle, scaleX, sizeY,
                colorRed, colorGreen, colorBlue,
                cmple_engine::shader_default_text, model_matrix);
            break;

        case FT_TIMES_NEW_ROMAN:
            cmple_engine::font_default_times_new_roman.DrawText(text, posX, posY,
                rotateAngle, scaleX, sizeY,
                colorRed, colorGreen, colorBlue,
                cmple_engine::shader_default_text, model_matrix);
            break;
        }
    }
}

void draw_sprite(Sprite sprite, float posX, float posY,
    float rotateAngle, float scaleX, float scaleY,
    float colorRed, float colorGreen, float colorBlue) {

    if (cmple_engine::mutex_display_2d_enabled) {
        glm::mat4 model_matrix = glm::mat4(1.0f);
        sprite.Draw(posX, posY, rotateAngle, scaleX, scaleY, colorRed, colorGreen, colorBlue, cmple_engine::shader_default_2d, model_matrix);
    }
}

void draw_model(Model model, float posX, float posY, float posZ,
    float rotateAngle, float rotateX, float rotateY, float rotateZ,
    float scaleX, float scaleY, float scaleZ) {

    if (cmple_engine::mutex_display_3d_enabled) {
        glm::mat4 model_matrix = glm::mat4(1.0f);
        model.Draw(posX, posY, posZ, rotateAngle, rotateX, rotateY, rotateZ, scaleX, scaleY, scaleZ, cmple_engine::shader_default_3d, model_matrix);
    }
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
