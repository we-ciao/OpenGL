#include "stdafx.h"
#include "Boom.h"
#include "time.h"


Boom::Boom()
{
	rang = 1;
	boomTime = 3;
}


Boom::~Boom()
{
}
//��ը֮�� ��Ϊƽ��
void Boom::Destroy(int x,int y) {
	if (maze->getCellVal(x,y) == boom)
	{
		maze->setCellVal(x, y, normal);
		if (check(x + 1, y) && checkIsObstacle(x + 1, y))
			maze->setCellVal(x + 1, y, normal);
		if (check(x, y + 1) && checkIsObstacle(x, y + 1))
			maze->setCellVal(x, y + 1, normal);
		if (check(x - 1, y) && checkIsObstacle(x - 1, y))
			maze->setCellVal(x - 1, y, normal);
		if (check(x, y - 1) && checkIsObstacle(x, y - 1))
			maze->setCellVal(x, y - 1, normal);
	}
}

//ը���ڲ�����ը
void Boom::explose(int x,int y){
	if (maze->getCellVal(x, y) == boom)
	{
		maze->setCellVal(x, y, explosion);
		if(check(x+1,y) && checkIsObstacle(x + 1, y))
			maze->setCellVal(x + 1, y, explosion);
		if (check(x,y+1) && checkIsObstacle(x, y + 1))
			maze->setCellVal(x, y + 1, explosion);
		if (check(x - 1, y) && checkIsObstacle(x - 1, y))
		maze->setCellVal(x - 1, y, explosion);
		if (check(x, y - 1) && checkIsObstacle(x, y - 1))
		maze->setCellVal(x, y - 1, explosion);
	}
}

//�߽��ж�
bool Boom::check(int x,int y) {
	if (x >= 0 && x < MAZEROW && y >= 0 && y < MAZECOL)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Boom::checkIsObstacle(int x,int y) {
	if (maze->getCellVal(x, y) == obstacle)
	{
		return false;
	}
	else
	{
		return true;
	}
}
//�ж�ը���Ƿ�ﵽ��ըʱ��
bool Boom::isBoomTime(float time)
{
	 float  end, cost;
	 end = clock();
	 cost = end - time;
	 if (cost == boomTime)
		 return true;
	 else
		 return false;
}