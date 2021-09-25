#include "classes_implementation.h"

int x, y;
int data;

void player::Create() {
    x = 0;
    y = 0;
}

void player::Destroy() {

}

void player::Update() {
    // if(keyboard_is_pressed(KEY_UP))
    y += 5;
    // if(keyboard_is_pressed(KEY_DOWN))
    y -= 5;
}

void player::Draw3D() {

}

void player::Draw2D() {
    // draw_sprite(sprite_ball, x, y);
}

