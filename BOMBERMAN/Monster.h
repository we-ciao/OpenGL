#pragma once
#include "Maze.h"
enum Forward { top = 1, bottom = 3, left = 4, right = 2 };//����
class Monster
{
public:
	Monster();
	Monster(int x, int y);//���һ������Ĳ���λ��
	virtual ~Monster();
	Maze* maze;
	void Move(int x,int y);//�����ƶ�
	int m_x, m_y;//������ֵ�λ��
};

