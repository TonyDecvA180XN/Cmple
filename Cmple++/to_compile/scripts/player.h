#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "classes_implementation.h"

class player {
public:

	int x, y;
	int data;
	
	void Create();
	
	void Destroy();
	
	void Update();
	
	void Draw3D();
	
	void Draw2D();
	
};

#endif // PLAYER_H_INCLUDED
