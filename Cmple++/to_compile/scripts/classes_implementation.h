#include "controll.h"
#include "player.h"

using controll_typename = int;
using player_typename = int;

std::map <int, controll> controll_container;
std::map <int, player> player_container;

int controll_objects_number = 0;
int player_objects_number = 0;

int create_object_controll() {
	controll_container[controll_objects_number] = controll();
	controll_container[controll_objects_number].Create();
	return controll_objects_number++;
}

int create_object_player() {
	player_container[player_objects_number] = player();
	player_container[player_objects_number].Create();
	return player_objects_number++;
}

void destroy_object_controll(int num) {
	controll_container[num].Destroy();
	controll_container.erase(num);
}

void destroy_object_player(int num) {
	player_container[num].Destroy();
	player_container.erase(num);
}

