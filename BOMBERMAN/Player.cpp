#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	p_x = p_y = 0;
}

Player::~Player()
{
}
//Íæ¼ÒÒÆ¶¯
void Player::move(int key) {
		maze->setCellVal(p_x,p_y, normal);
		switch (key)
		{
		case VK_UP:p_forWard = top;
			if (borderCheck(p_x - 1, p_y)&&collisonCheck(maze->getCellVal(p_x -1,p_y)))
			{
				p_x--;
			}break;
		case VK_RIGHT:p_forWard = right;
			if (borderCheck(p_x, p_y + 1) && collisonCheck(maze->getCellVal(p_x, p_y + 1)))
			{
				p_y++;
			}break;
		case VK_DOWN:p_forWard = bottom;
			if (borderCheck(p_x + 1, p_y) && collisonCheck(maze->getCellVal(p_x + 1, p_y)))
			{
				p_x++;
			}break;
		case VK_LEFT:p_forWard = left;
			if (borderCheck(p_x, p_y - 1) && collisonCheck(maze->getCellVal(p_x, p_y - 1)))
			{
				p_y--;
			}break;
		case VK_SPACE:
		default:
			break;
		}
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
bool Player::collisonCheck(int val){
	if (val == obstacle)
	{
		return false;
	}
	else
	{
		return true;
	}
}