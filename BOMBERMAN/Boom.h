#pragma once
#include "Maze.h"
class Boom
{
public:
	Boom();
	virtual ~Boom();
	int x, y;
	void Destroy(int x, int y);//爆炸后变为平地
	void DestroyPlus(int x, int y);
	void explose(int  ,int );//爆炸
	void explosePlus(int x, int y);//装备升级之后爆炸效果
	bool check(int x, int y);//边缘爆炸检查
	bool checkIsObstacle(int x, int y);//检查是不是障碍物
	Maze* maze;
};

