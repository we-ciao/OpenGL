#pragma once
#include "Maze.h"

enum Forward { top=1, bottom=3, left=4, right=2 };
class Player
{
public:
	Player();
	virtual ~Player();
	int p_x,p_y,p_forWard;
	bool borderCheck(int ,int );
	void move(int key);
	Maze* maze;
};

