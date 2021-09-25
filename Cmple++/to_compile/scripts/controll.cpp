#include "classes_implementation.h"

int Time;
player_typename my_player;

void controll::Create() {
    my_player = create_object_player();
    player_typename nnn;
    player_container[nnn].data++;
    Time = 0;
}

void controll::Destroy() {

}

void controll::Update() {
    Time += 1;
    if(rand()%10 == 0)
        player_container[my_player].x += 10;
}

void controll::Draw3D() {

}

void controll::Draw2D() {
    // draw_text(32, 48, to_string(Time));
}

