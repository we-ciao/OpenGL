#include "stdafx.h"
#include "Monster.h"
#include <time.h>


Monster::Monster()
{

}


Monster::~Monster()
{
}
//怪物移动
void Monster::Move(int x, int y) {
	srand((unsigned)time(0));
	switch (rand() % 4 + 1)
	{
	case top:maze->setCellVal(x, y, monsterUp);
		for (x; x != -1 || x != MAZEROW;x--)
		{
			maze->setCellVal(x + 1, y, normal);
			maze->setCellVal(x, y, monsterUp);
		}
		break;
	case right:maze->setCellVal(x, y, monsterRight);
		for (y ; y != -1 || y != MAZECOL; y++)
		{
			maze->setCellVal(x, y-1, normal);
			maze->setCellVal(x, y, monsterUp);
		}
		break;
	case bottom:maze->setCellVal(x, y, monsterDown);
		for (x; x != -1 || x != MAZEROW; x++)
		{
			maze->setCellVal(x - 1, y, normal);
			maze->setCellVal(x, y, monsterUp);
		}
		break;
	case left:maze->setCellVal(x, y, monsterLeft);
		for (y; y != -1 || y != MAZECOL; y--)
		{
			maze->setCellVal(x, y + 1, normal);
			maze->setCellVal(x, y, monsterUp);
		}
		break;
	default:
		break;
	}
}
//初始化怪物生成位置
Monster::Monster(int x,int y)
{
	m_x = x;
	m_y = y;
}
