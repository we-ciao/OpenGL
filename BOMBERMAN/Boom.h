#pragma once
#include "Maze.h"
class Boom
{
public:
	Boom();
	virtual ~Boom();
	int x, y;
	int rang,boomTime;
	void Destroy(int x, int y);//��ը���Ϊƽ��
	void explose(int  ,int );//��ը
	bool check(int x, int y);//��Ե��ը���
	bool checkIsObstacle(int x, int y);//����ǲ����ϰ���
	bool isBoomTime(float time);
	Maze* maze;
};

