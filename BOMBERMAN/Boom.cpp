#include "stdafx.h"
#include "Boom.h"
#include "time.h"


Boom::Boom()
{
}

Boom::Boom(int inX, int inY, int inId, int irange, double istartTime)
{
	x = inX;
	y = inY;
	boomId = inId;
	rang = irange;
	startTime = istartTime;
}

Boom::~Boom()
{
}
//��ը֮�� ��Ϊƽ��
//void Boom::Destroy(int x,int y) {
//	if (maze->getCellVal(x,y) == boom)
//	{
//		maze->setCellVal(x, y, normal);
//		if (check(x + 1, y) && eachCase(x + 1, y))
//			maze->setCellVal(x + 1, y, normal);
//		if (check(x, y + 1) && eachCase(x, y + 1))
//			maze->setCellVal(x, y + 1, normal);
//		if (check(x - 1, y) && eachCase(x - 1, y))
//			maze->setCellVal(x - 1, y, normal);
//		if (check(x, y - 1) && eachCase(x, y - 1))
//			maze->setCellVal(x, y - 1, normal);
//	}
//}

//ը���ڲ�����ը
void Boom::explose(){

	//����
	for (int newX = this->x+1; newX <= x + rang && newX < MAZEROW; newX++) {
		if (eachCase(newX, y) == false)
			break;
		maze->setCellVal(newX, y, explosion);
	}
		
	//����
	for (int newX = this->x - 1; newX >= x - rang - 1 && newX >= 0; newX--)
	{
		if (eachCase(newX, y) == false)
			break;
		maze->setCellVal(newX, y, explosion);
	}
		
	//����
	for (int newY = this->y + 1; newY <= y + rang && newY < MAZECOL; newY++)
	{
		if (eachCase(x, newY) == false)
			break;

		maze->setCellVal(x, newY, explosion);
	}
	//����
	for (int newY = this->y - 1; newY >= y - rang - 1 && newY >= 0; newY--)
	{
		if (eachCase(x, newY) == false)
			break;
		maze->setCellVal(x, newY, explosion);
	}
}


bool Boom::eachCase(int nx,int ny) {
	//game->isSomeone(x, y);�ж��ǲ������
	if (maze->getCellVal(nx, ny) != normal&&nx!=x&&ny!=y)
	{
		return false;
	}
	else
	{
		return true;
	}
}
//�ж�ը���Ƿ�ﵽ��ըʱ��
bool Boom::timeOver(double time)
{
	double atTime = time - startTime;
	if (atTime >= boomTime) {
		return true;
	}
	return false;
}