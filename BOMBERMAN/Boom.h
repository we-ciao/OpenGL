#pragma once
#include "Maze.h"
class Boom
{
public:
	Boom();
	virtual ~Boom();
	int x, y;
	void Destroy(int x, int y);//��ը���Ϊƽ��
	void DestroyPlus(int x, int y);
	void explose(int  ,int );//��ը
	void explosePlus(int x, int y);//װ������֮��ըЧ��
	bool check(int x, int y);//��Ե��ը���
	bool checkIsObstacle(int x, int y);//����ǲ����ϰ���
	Maze* maze;
};

