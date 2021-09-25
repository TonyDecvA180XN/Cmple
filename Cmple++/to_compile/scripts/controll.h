#ifndef CONTROLL_H_INCLUDED
#define CONTROLL_H_INCLUDED

#include "classes_implementation.h"

class controll {
public:

	int Time;
	player_typename my_player;
	
	void Create();
	
	void Destroy();
	
	void Update();
	
	void Draw3D();
	
	void Draw2D();
	
};

#endif // CONTROLL_H_INCLUDED
