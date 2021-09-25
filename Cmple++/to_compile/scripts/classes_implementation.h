#ifndef CLASSES_IMPLEMENTATION_H_INCLUDED
#define CLASSES_IMPLEMENTATION_H_INCLUDED

#include <map>

class controll;
class player;

extern std::map <int, controll> controll_container;
extern std::map <int, player> player_container;

extern int controll_objects_number;
extern int player_objects_number;

using controll_typename = int;
using player_typename = int;

int create_object_controll();
int create_object_player();

void destroy_object_controll(int);
void destroy_object_player(int);

#include "controll.h"
#include "player.h"


#endif // CLASSES_IMPLEMENTATION_H_INCLUDED
