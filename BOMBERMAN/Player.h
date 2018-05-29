#pragma once
#include "Maze.h"
#include "Boom.h"
#include <list>

#include"gl/gl.h"
#include"gl/glu.h"


class Player
{
public:
	Player();
	virtual ~Player();
	Maze * maze;										//�Թ�
	std::list<Boom*> *boomlist;						//ը������
	void move(int key, double time);				//����ƶ�

private:
	int p_x,p_y,p_forWard;							//�Թ�����p_x,p_y,��ҳ���
	int range;
	int boomid;
	bool borderCheck(int ,int );					//�߽���
	bool collisonCheck(int);						//��ײ���
	Boom* bullet;

};