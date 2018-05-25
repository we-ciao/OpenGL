#pragma once
#include "Maze.h"
class Boom
{
public:
	Boom();
	virtual ~Boom();
	int x, y;
	bool borderCheck(int, int);	//±ß½ç¼ì²é
	void Destroy();
	void explose(int  ,int );
	Maze* maze;
};

