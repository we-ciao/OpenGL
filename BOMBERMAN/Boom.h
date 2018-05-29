#pragma once
#include"Maze.h"

class Boom
{
public:
	Boom();
	Boom(int x, int y, int id, int range, double startTimer);
	virtual ~Boom();
	int x, y, startTime, rang, boomTime, boomId;
	void explose(Maze* maze);//爆炸
	bool Boom::eachCase(int x, int y, Maze* maze);//遍历四周是否为空地
	bool timeOver(double time);
};

