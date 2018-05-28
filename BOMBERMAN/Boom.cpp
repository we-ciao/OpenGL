#include "stdafx.h"
#include "Boom.h"


Boom::Boom()
{

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
//��ը֮�� ��Ϊƽ��
void Boom::DestroyPlus(int x, int y) {
	if (maze->getCellVal(x, y) == explosion)
	{
		maze->setCellVal(x, y, normal);
		if (check(x + 1, y) && check(x + 2, y) && checkIsObstacle(x + 1, y) && checkIsObstacle(x + 2, y))
		{
			maze->setCellVal(x + 1, y, normal);
			maze->setCellVal(x + 2, y, normal);
		}

		if (check(x, y + 1) && check(x, y + 2) && checkIsObstacle(x, y + 1) && checkIsObstacle(x, y + 2)) {
			maze->setCellVal(x, y + 1, normal);
			maze->setCellVal(x, y + 2, normal);
		}

		if (check(x - 1, y) && check(x - 2, y) && checkIsObstacle(x - 1, y) && checkIsObstacle(x - 2, y))
		{
			maze->setCellVal(x - 1, y, normal);
			maze->setCellVal(x - 2, y, normal);
		}

		if (check(x, y - 1) && check(x, y - 2) && checkIsObstacle(x, y - 1) && checkIsObstacle(x, y - 2))
		{
			maze->setCellVal(x, y - 1, normal);
			maze->setCellVal(x, y - 2, normal);
		}
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
//װ������֮��ըЧ��
void Boom::explosePlus(int x, int y) {
	if (maze->getCellVal(x, y) == boom)
	{
		maze->setCellVal(x, y, explosion);
		if (check(x + 1, y) && check(x + 2, y) && checkIsObstacle(x + 1, y) && checkIsObstacle(x + 2, y))
		{
			maze->setCellVal(x + 1, y, explosion);
			maze->setCellVal(x + 2, y, explosion);
		}
			
		if (check(x, y + 1) && check(x, y + 2) && checkIsObstacle(x, y + 1) && checkIsObstacle(x, y + 2)) {
			maze->setCellVal(x, y + 1, explosion);
			maze->setCellVal(x, y + 2, explosion);
		}
			
		if (check(x - 1, y) && check(x - 2, y) && checkIsObstacle(x - 1, y) && checkIsObstacle(x - 2, y))
		{
			maze->setCellVal(x - 1, y, explosion);
			maze->setCellVal(x - 2, y, explosion);
		}
			
		if (check(x, y - 1) && check(x, y - 2) && checkIsObstacle(x, y - 1) && checkIsObstacle(x, y - 2))
		{
			maze->setCellVal(x, y - 1, explosion);
			maze->setCellVal(x, y - 2, explosion);
		}
			
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