#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	p_x = p_y = 0;
}


Player::~Player()
{
}

bool Player::borderCheck(int x,int y) {
	if (x<0||x>MAZEROW-1 || y<0 || y>MAZECOL - 1)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Player::move(int key) {
		maze->setCellVal(p_x,p_y, normal);
		switch (key)
		{
		case VK_UP:p_forWard = top;
			if (borderCheck(p_x - 1, p_y))
			{
				p_x--;
			}break;
		case VK_RIGHT:p_forWard = right;
			if (borderCheck(p_x, p_y + 1))
			{
				p_y++;
			}break;
		case VK_DOWN:p_forWard = bottom;
			if (borderCheck(p_x + 1, p_y))
			{
				p_x++;
			}break;
		case VK_LEFT:p_forWard = left;
			if (borderCheck(p_x, p_y - 1))
			{
				p_y--;
			}break;
		default:
			break;
		}
		maze->setCellVal(p_x, p_y, 90 + p_forWard);
		
}