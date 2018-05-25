#include "stdafx.h"
#include "Boom.h"


Boom::Boom()
{
}


Boom::~Boom()
{
}
void Boom::Destroy() {
	for (int i = 0; i < MAZEROW; i++)
	{
		for (int j = 0; j < MAZECOL; j++)
		{
			if (maze->getCellVal(i, j) == boom)
			{
				maze->setCellVal(i, j, normal);
			}
		}
	}
}
//±ß½ç¼ì²é
bool Boom::borderCheck(int x, int y) {
	if (x<0 || x>MAZEROW - 1 || y<0 || y>MAZECOL - 1)
	{
		return false;
	}
	else
	{
		return true;
	}
}
void Boom::explose(int x,int y){
	if (maze->getCellVal(x,y)!=obstacle&&borderCheck(x,y))
	{
		maze->setCellVal(x - 1, y, boom);
		maze->setCellVal(x, y + 1, boom);
		maze->setCellVal(x + 1, y, boom);
		maze->setCellVal(x, y - 1, boom);
	}
}