#pragma once
#include "Maze.h"
#include "Boom.h"
#include <list>


class Player
{
public:
	Player();
	virtual ~Player();
	Maze * maze;										//迷宫
	std::list<Boom*> *boomlist;						//炸弹队列
	void move(int key, double time);				//玩家移动

private:
	int p_x,p_y,p_forWard;							//迷宫坐标p_x,p_y,玩家朝向
	int range;
	int boomid;
	bool borderCheck(int ,int );					//边界检查
	bool collisonCheck(int);						//碰撞检测
	Boom* bullet;
};

