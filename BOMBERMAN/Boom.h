#pragma once
#include"Maze.h"

class Boom
{
public:
	Boom();
	Boom(int x, int y, int id, int range, double startTimer);//���캯��
	virtual ~Boom();
	int x, y, startTime, rang, boomTime, boomId;//���� ��ʼʱ�� ��ը��Χ ��ըʱ�� id
	void explose(Maze* maze);//��ը
	bool Boom::eachCase(int x, int y, Maze* maze);//���������Ƿ�Ϊ�յ�
	bool timeOver(double time);//�ж��Ƿ񵽴ﱬըʱ��
};

