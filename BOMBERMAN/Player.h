#pragma once
#include "Maze.h"
#include "Boom.h"

enum Forward { top=1, bottom=3, left=4, right=2 };//����
class Player
{
public:
	Player();
	virtual ~Player();
	int p_x,p_y,p_forWard;			//�Թ�����p_x,p_y,��ҳ���
	bool borderCheck(int ,int );	//�߽���
	bool collisonCheck(int);		//��ײ���
	void move(int key);				//����ƶ�
	Maze* maze;						//�Թ�
	Boom* bullet;
};

