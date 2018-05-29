#include "stdafx.h"
#include "Boom.h"
#include "time.h"


Boom::Boom()
{
	boomTime = 30;
}

Boom::Boom(int inX, int inY, int inId, int irange, double istartTime)
{
	boomTime = 30;
	x = inX;
	y = inY;
	boomId = inId;
	rang = irange;
	startTime = istartTime;
}

Boom::~Boom()
{
}
//爆炸之后 变为平地
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

//炸弹在产生后爆炸
void Boom::explose(Maze* maze){
	int count = 0;//计数器
	//向下
	for (int newX = this->x; newX <= x + rang && newX < MAZEROW; newX++) {
		if (eachCase(newX, y, maze) == false )
			break;
		if (maze->getCellVal(newX, y) != normal)
		{
			
			maze->setCellVal(newX, y, explosion);
			
			if(count == 1)
			break;
		}
		count++;
		maze->setCellVal(newX, y, explosion);
	}
		
	//向上
	for (int newX = this->x - 1; newX >= x - rang && newX >= 0; newX--)
	{
		if (eachCase(newX, y, maze) == false)
			break;
		if (maze->getCellVal(newX, y) != normal)
		{
			maze->setCellVal(newX, y, explosion);
			break;
		}
		maze->setCellVal(newX, y, explosion);
	}
		
	//向右
	for (int newY = this->y + 1; newY <= y + rang && newY < MAZECOL; newY++)
	{
		if (eachCase(x, newY, maze) == false)
			break;
		if (maze->getCellVal(x, newY) != normal)
		{
			maze->setCellVal(x, newY, explosion);
			break;
		}
		maze->setCellVal(x, newY, explosion);
	}
	//向左
	for (int newY = this->y - 1; newY >= y - rang && newY >= 0; newY--)
	{
		if (eachCase(x, newY, maze) == false)
			break;
		if (maze->getCellVal(x, newY) != normal)
		{
			maze->setCellVal(x, newY, explosion);
			break;
		}
		maze->setCellVal(x, newY, explosion);
	}
}


bool Boom::eachCase(int nx,int ny,Maze* maze) {
	//game->isSomeone(x, y);判断是不是玩家
	if (maze->getCellVal(nx, ny) != obstacle)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//判断炸弹是否达到爆炸时间
bool Boom::timeOver(double time)
{
	double atTime = time - startTime;
	if (atTime >= boomTime) {
		return true;
	}
	return false;
}