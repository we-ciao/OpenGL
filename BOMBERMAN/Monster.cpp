#include "stdafx.h"
#include "Monster.h"
#include <time.h>


Monster::Monster()
{

}


Monster::~Monster()
{
}
//�����ƶ�
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
//��ʼ����������λ��
Monster::Monster(int x,int y)
{
	m_x = x;
	m_y = y;
}
