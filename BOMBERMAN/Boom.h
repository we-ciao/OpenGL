#pragma once
#include"Maze.h"

class Boom
{
public:
	Boom();
	Boom(int x, int y, int id, int range, double startTimer);
	virtual ~Boom();
	int x, y, startTime, rang, boomTime, boomId;
	void explose(Maze* maze);//��ը
	bool Boom::eachCase(int x, int y, Maze* maze);//���������Ƿ�Ϊ�յ�
	bool timeOver(double time);
};

