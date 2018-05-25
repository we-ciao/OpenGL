#pragma once
#include "Maze.h"
#include "Boom.h"

enum Forward { top=1, bottom=3, left=4, right=2 };//方向
class Player
{
public:
	Player();
	virtual ~Player();
	int p_x,p_y,p_forWard;			//迷宫坐标p_x,p_y,玩家朝向
	bool borderCheck(int ,int );	//边界检查
	bool collisonCheck(int);		//碰撞检测
	void move(int key);				//玩家移动
	Maze* maze;						//迷宫
};

