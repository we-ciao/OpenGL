#pragma once
#include "Maze.h"
class Boom
{
public:
	Boom();
	virtual ~Boom();
	int x, y;
	int rang,boomTime;
	void Destroy(int x, int y);//爆炸后变为平地
	void explose(int  ,int );//爆炸
	bool check(int x, int y);//边缘爆炸检查
	bool checkIsObstacle(int x, int y);//检查是不是障碍物
	bool isBoomTime(float time);
	Maze* maze;
};

