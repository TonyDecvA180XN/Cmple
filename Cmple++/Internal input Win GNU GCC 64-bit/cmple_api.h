#ifndef CMPLE_API_H_INCLUDED
#define CMPLE_API_H_INCLUDED

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
#include "cmple_engine.h"

using cmple_keyboard_key = unsigned int;
using cmple_mouse_button = unsigned int;
using cmple_font         = unsigned int;

const cmple_keyboard_key KB_SPACE            = 32;
const cmple_keyboard_key KB_APOSTROPHE       = 39;  /* ' */
const cmple_keyboard_key KB_COMMA            = 44;  /* , */
const cmple_keyboard_key KB_MINUS            = 45;  /* - */
const cmple_keyboard_key KB_PERIOD           = 46;  /* . */
const cmple_keyboard_key KB_SLASH            = 47;  /* / */
const cmple_keyboard_key KB_0                = 48;
const cmple_keyboard_key KB_1                = 49;
const cmple_keyboard_key KB_2                = 50;
const cmple_keyboard_key KB_3                = 51;
const cmple_keyboard_key KB_4                = 52;
const cmple_keyboard_key KB_5                = 53;
const cmple_keyboard_key KB_6                = 54;
const cmple_keyboard_key KB_7                = 55;
const cmple_keyboard_key KB_8                = 56;
const cmple_keyboard_key KB_9                = 57;
const cmple_keyboard_key KB_SEMICOLON        = 59;  /* ; */
const cmple_keyboard_key KB_EQUAL            = 61;  /* = */
const cmple_keyboard_key KB_A                = 65;
const cmple_keyboard_key KB_B                = 66;
const cmple_keyboard_key KB_C                = 67;
const cmple_keyboard_key KB_D                = 68;
const cmple_keyboard_key KB_E                = 69;
const cmple_keyboard_key KB_F                = 70;
const cmple_keyboard_key KB_G                = 71;
const cmple_keyboard_key KB_H                = 72;
const cmple_keyboard_key KB_I                = 73;
const cmple_keyboard_key KB_J                = 74;
const cmple_keyboard_key KB_K                = 75;
const cmple_keyboard_key KB_L                = 76;
const cmple_keyboard_key KB_M                = 77;
const cmple_keyboard_key KB_N                = 78;
const cmple_keyboard_key KB_O                = 79;
const cmple_keyboard_key KB_P                = 80;
const cmple_keyboard_key KB_Q                = 81;
const cmple_keyboard_key KB_R                = 82;
const cmple_keyboard_key KB_S                = 83;
const cmple_keyboard_key KB_T                = 84;
const cmple_keyboard_key KB_U                = 85;
const cmple_keyboard_key KB_V                = 86;
const cmple_keyboard_key KB_W                = 87;
const cmple_keyboard_key KB_X                = 88;
const cmple_keyboard_key KB_Y                = 89;
const cmple_keyboard_key KB_Z                = 90;
const cmple_keyboard_key KB_LEFT_BRACKET     = 91;  /* [ */
const cmple_keyboard_key KB_BACKSLASH        = 92;  /* \ */
const cmple_keyboard_key KB_RIGHT_BRACKET    = 93;  /* ] */
const cmple_keyboard_key KB_GRAVE_ACCENT     = 96;  /* ` */
const cmple_keyboard_key KB_WORLD_1          = 161; /* non-US #1 */
const cmple_keyboard_key KB_WORLD_2          = 162; /* non-US #2 */

/* Function keys */
const cmple_keyboard_key KB_ESCAPE           = 256;
const cmple_keyboard_key KB_ENTER            = 257;
const cmple_keyboard_key KB_TAB              = 258;
const cmple_keyboard_key KB_BACKSPACE        = 259;
const cmple_keyboard_key KB_INSERT           = 260;
const cmple_keyboard_key KB_DELETE           = 261;
const cmple_keyboard_key KB_RIGHT            = 262;
const cmple_keyboard_key KB_LEFT             = 263;
const cmple_keyboard_key KB_DOWN             = 264;
const cmple_keyboard_key KB_UP               = 265;
const cmple_keyboard_key KB_PAGE_UP          = 266;
const cmple_keyboard_key KB_PAGE_DOWN        = 267;
const cmple_keyboard_key KB_HOME             = 268;
const cmple_keyboard_key KB_END              = 269;
const cmple_keyboard_key KB_CAPS_LOCK        = 280;
const cmple_keyboard_key KB_SCROLL_LOCK      = 281;
const cmple_keyboard_key KB_NUM_LOCK         = 282;
const cmple_keyboard_key KB_PRINT_SCREEN     = 283;
const cmple_keyboard_key KB_PAUSE            = 284;
const cmple_keyboard_key KB_F1               = 290;
const cmple_keyboard_key KB_F2               = 291;
const cmple_keyboard_key KB_F3               = 292;
const cmple_keyboard_key KB_F4               = 293;
const cmple_keyboard_key KB_F5               = 294;
const cmple_keyboard_key KB_F6               = 295;
const cmple_keyboard_key KB_F7               = 296;
const cmple_keyboard_key KB_F8               = 297;
const cmple_keyboard_key KB_F9               = 298;
const cmple_keyboard_key KB_F10              = 299;
const cmple_keyboard_key KB_F11              = 300;
const cmple_keyboard_key KB_F12              = 301;
const cmple_keyboard_key KB_F13              = 302;
const cmple_keyboard_key KB_F14              = 303;
const cmple_keyboard_key KB_F15              = 304;
const cmple_keyboard_key KB_F16              = 305;
const cmple_keyboard_key KB_F17              = 306;
const cmple_keyboard_key KB_F18              = 307;
const cmple_keyboard_key KB_F19              = 308;
const cmple_keyboard_key KB_F20              = 309;
const cmple_keyboard_key KB_F21              = 310;
const cmple_keyboard_key KB_F22              = 311;
const cmple_keyboard_key KB_F23              = 312;
const cmple_keyboard_key KB_F24              = 313;
const cmple_keyboard_key KB_F25              = 314;
const cmple_keyboard_key KB_KP_0             = 320;
const cmple_keyboard_key KB_KP_1             = 321;
const cmple_keyboard_key KB_KP_2             = 322;
const cmple_keyboard_key KB_KP_3             = 323;
const cmple_keyboard_key KB_KP_4             = 324;
const cmple_keyboard_key KB_KP_5             = 325;
const cmple_keyboard_key KB_KP_6             = 326;
const cmple_keyboard_key KB_KP_7             = 327;
const cmple_keyboard_key KB_KP_8             = 328;
const cmple_keyboard_key KB_KP_9             = 329;
const cmple_keyboard_key KB_KP_DECIMAL       = 330;
const cmple_keyboard_key KB_KP_DIVIDE        = 331;
const cmple_keyboard_key KB_KP_MULTIPLY      = 332;
const cmple_keyboard_key KB_KP_SUBTRACT      = 333;
const cmple_keyboard_key KB_KP_ADD           = 334;
const cmple_keyboard_key KB_KP_ENTER         = 335;
const cmple_keyboard_key KB_KP_EQUAL         = 336;
const cmple_keyboard_key KB_LEFT_SHIFT       = 340;
const cmple_keyboard_key KB_LEFT_CONTROL     = 341;
const cmple_keyboard_key KB_LEFT_ALT         = 342;
const cmple_keyboard_key KB_LEFT_SUPER       = 343;
const cmple_keyboard_key KB_RIGHT_SHIFT      = 344;
const cmple_keyboard_key KB_RIGHT_CONTROL    = 345;
const cmple_keyboard_key KB_RIGHT_ALT        = 346;
const cmple_keyboard_key KB_RIGHT_SUPER      = 347;
const cmple_keyboard_key KB_MENU             = 348;

const cmple_keyboard_key KB_LAST             = KB_MENU;

const cmple_mouse_button MB_1       = 0;
const cmple_mouse_button MB_2       = 1;
const cmple_mouse_button MB_3       = 2;
const cmple_mouse_button MB_4       = 3;
const cmple_mouse_button MB_5       = 4;
const cmple_mouse_button MB_6       = 5;
const cmple_mouse_button MB_7       = 6;
const cmple_mouse_button MB_8       = 7;
const cmple_mouse_button MB_LAST    = MB_8;
const cmple_mouse_button MB_LEFT    = MB_1;
const cmple_mouse_button MB_RIGHT   = MB_2;
const cmple_mouse_button MB_MIDDLE  = MB_3;

const cmple_font FT_ARIAL           = 0;
const cmple_font FT_CALIBRI         = 1;
const cmple_font FT_TIMES_NEW_ROMAN = 2;

namespace cmple_api {
    const int keyboard_key_first = 32;
    const int keyboard_key_last = 348;

    const int mouse_key_first = 0;
    const int mouse_key_last = 7;

    extern bool keyboard[];
    extern bool keyboard_pressed[];
    extern bool keyboard_pressed_block[];
    extern bool keyboard_released[];
    extern bool keyboard_released_block[];
    extern bool mouse[];
    extern bool mouse_pressed[];
    extern bool mouse_pressed_block[];
    extern bool mouse_released[];
    extern bool mouse_released_block[];

    void keyboard_update(GLFWwindow* window);
    void mouse_update(GLFWwindow* window);
}

bool keyboard(cmple_keyboard_key key);
bool keyboard_pressed(cmple_keyboard_key key);
bool keyboard_released(cmple_keyboard_key key);

bool mouse(cmple_mouse_button button);
bool mouse_pressed(cmple_mouse_button button);
bool mouse_released(cmple_mouse_button button);

int mouse_x();
int mouse_y();

void set_resolution(unsigned int width, unsigned int height);
void set_window_name(std::string name);
void set_frame_per_second(double fps);
void end_program();

void set_camera_position_by_look_at(float posX, float posY, float posZ,
    float targetX, float targetY, float targetZ);

void set_camera_position_by_angles(float posX, float posY, float posZ,
    float upX, float upY, float upZ, float yaw, float pitch);

void set_exposure(float exposure);

void set_directional_light_direction(float dirX, float dirY, float dirZ);
void set_directional_light_color(float colorRed, float colorGreen, float colorBlue);

void set_point_light_position(int index, float posX, float posY, float posZ);
void set_point_light_color(int index, float colorRed, float colorGreen, float colorBlue);

void set_spot_light_position(float posX, float posY, float posZ);
void set_spot_light_color(float colorRed, float colorGreen, float colorBlue);
void set_spot_light_direction(float dirX, float dirY, float dirZ);
void set_spot_light_angle(float cutOff, float outerCutOff);

void draw_text(std::string text, cmple_font font, float posX, float posY,
    float angleRotate, float scaleX, float scaleY,
    float colorRed, float colorGreen, float colorBlue);

void draw_sprite(Sprite sprite, float posX, float posY,
    float rotateAngle, float scaleX, float scaleY,
    float colorRed, float colorGreen, float colorBlue);

void draw_model(Model model, float posX, float posY, float posZ,
    float rotateAngle, float rotateX, float rotateY, float rotateZ,
    float scaleX, float scaleY, float scaleZ);

void sound_play(Sound sound);
void sound_stop(Sound sound);
bool sound_is_playing(Sound sound);

#endif // CMPLE_API_H_INCLUDED
