#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	range = 2;
	boomid = 0;
	p_x = p_y = 0;
	p_forWard = bottom;
}

Player::~Player()
{
}
//Íæ¼ÒÒÆ¶¯
void Player::move(int key,double time) {
	int n_x = p_x, n_y = p_y;
	switch (key)
	{
	case VK_SPACE:
		if (maze->getCellVal(p_x, p_y) != boom) {
			maze->setCellVal(p_x, p_y, 94 + p_forWard);
			bullet = new Boom(p_x, p_y, boomid++, range, time);
			boomlist->push_back(bullet);
		}
		return;
		break;
	case VK_UP:
		p_forWard = top;
		n_x--;
		break;
	case VK_RIGHT:
		p_forWard = right;
		n_y++;
		break;
	case VK_DOWN:
		p_forWard = bottom;
		n_x++;
		break;
	case VK_LEFT:
		p_forWard = left;
		n_y--;
		break;
	default:
		break;
	}

	if (!borderCheck(n_x, n_y) || !collisonCheck(maze->getCellVal(n_x, n_y)))
		return;


	if (maze->getCellVal(p_x, p_y) >= playerWboomUp
		&& maze->getCellVal(p_x, p_y) <= playerWboomLeft)
	{
		maze->setCellVal(p_x, p_y, boom);
		//bullet->maze = maze;
		//bullet->explose(p_x, p_y);
		//bullet->explose();
		/*Sleep(3000);*/
		//bullet->DestroyPlus(p_x, p_y);
	}
	else
	{
		maze->setCellVal(p_x, p_y, normal);
	}
	 p_x= n_x ,  p_y= n_y ;
	 maze->setCellVal(p_x, p_y, 90 + p_forWard);
}
//±ß½ç¼ì²é
bool Player::borderCheck(int x, int y) {
	if (x<0 || x>MAZEROW - 1 || y<0 || y>MAZECOL - 1)
	{
		return false;
	}
	else
	{
		return true;
	}
}
//Åö×²¼ì²â
bool Player::collisonCheck(int val) {
	if (val != normal)
	{
		return false;
	}
	else
	{
		return true;
	}
}