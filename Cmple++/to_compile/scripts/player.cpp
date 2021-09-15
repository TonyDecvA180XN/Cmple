#include "player.h"

int x, y;

void player::Create() {
    x = 0
    y = 0
}

void player::Destroy() {

}

void player::Update() {
    if(keyboard_is_pressed(KEY_UP))
        y += 5;
    if(keyboard_is_pressed(KEY_DOWN))
        y -= 5;
}

void player::Draw() {
    draw_sprite(sprite_ball, x, y);
}

