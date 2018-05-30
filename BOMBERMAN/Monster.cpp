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

}
//初始化怪物生成位置
Monster::Monster(int x,int y)
{
	m_forWard = bottom;
	m_x = x;
	m_y = y;
	alive = true;
}

bool Monster::collisonCheck(int val)
{
	if (val != normal)
	{
		return true;
	}
	else
	{
		return false;
	}
}

