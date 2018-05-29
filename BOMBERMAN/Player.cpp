#include "stdafx.h"
#include "Player.h"
#include "Monster.h"

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
//����ƶ�
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
		maze->play_forward = playerUp1;
		n_x--;
		maze->play_x = 0;
		maze->play_y = -0.25;
		break;
	case VK_RIGHT:
		p_forWard = right;
		n_y++;
		maze->play_x = 0.25;
		maze->play_y = 0;
		maze->play_forward = playerRight1;
		break;
	case VK_DOWN:
		p_forWard = bottom;
		n_x++;
		maze->play_x = 0;
		maze->play_y = 0.25;
		maze->play_forward = playerDown1;
		break;
	case VK_LEFT:
		p_forWard = left;
		n_y--;
		maze->play_x = -0.25;
		maze->play_y = 0;
		maze->play_forward = playerLeft1;
		break;
	default:
		break;
	}

	if (!borderCheck(n_x, n_y) || !collisonCheck(maze->getCellVal(n_x, n_y)))
		return;

	maze->isStop = false;
	maze->count = 0;

	if (maze->getCellVal(p_x, p_y) >= playerWboomUp
		&& maze->getCellVal(p_x, p_y) <= playerWboomLeft)
	{
		maze->setCellVal(p_x, p_y, boom);
	}
	else
	{
		maze->setCellVal(p_x, p_y, normal);
	}
	 p_x= n_x ,  p_y= n_y ;
	 maze->setCellVal(p_x, p_y, 90 + p_forWard);
}
//�߽���
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
//��ײ���
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


//
//
//void Player::drawSprite()
//{
//	const int step = 800;
//	count++;
//
//	if (isStop) {
//		if (p_forWard == top) {
//			drawRect(texture, index[0][1][0], index[0][1][1]);
//		}
//		else if (p_forWard == bottom) {
//			drawRect(texture, index[3][1][0], index[3][1][1]);
//		}
//		else if (p_forWard == left) {
//			drawRect(texture, index[1][1][0], index[1][1][1]);
//		}
//		else if (p_forWard == right) {
//			drawRect(texture, index[2][1][0], index[2][1][1]);
//		}
//	}
//	else if (p_forWard == top) {
//		if (count <= step) {
//			drawRect(texture, index[0][0][0], index[0][0][1]);
//		}
//		else if (count > step&&count <= step * 2) {
//			drawRect(texture, index[0][1][0], index[0][1][1]);
//		}
//		else if (count > step * 2 && count <= step * 3) {
//			drawRect(texture, index[0][2][0], index[0][2][1]);
//		}
//	}
//	else if (p_forWard == bottom) {
//		if (count <= step) {
//			drawRect(texture, index[3][0][0], index[3][0][1]);
//		}
//		else if (count > step && count <= step * 2) {
//			drawRect(texture, index[3][1][0], index[3][1][1]);
//		}
//		else if (count > step * 2 && count <= step * 3) {
//			drawRect(texture, index[3][2][0], index[3][2][1]);
//		}
//	}
//	else if (p_forWard == left) {
//		if (count <= step) {
//			drawRect(texture, index[1][0][0], index[1][0][1]);
//		}
//		else if (count > step && count <= step * 2) {
//			drawRect(texture, index[1][1][0], index[1][1][1]);
//		}
//		else if (count > step * 2 && count <= step * 3) {
//			drawRect(texture, index[1][2][0], index[1][2][1]);
//		}
//	}
//	else if (p_forWard == right) {
//		if (count <= step) {
//			drawRect(texture, index[2][0][0], index[2][0][1]);
//		}
//		else if (count > step && count <= step * 2) {
//			drawRect(texture, index[2][1][0], index[2][1][1]);
//		}
//		else if (count > step * 2 && count <= step * 3) {
//			drawRect(texture, index[2][2][0], index[2][2][1]);
//		}
//	}
//	if (count%step == 0) {
//		if (count2 == count3) {
//			if (p_forWard == top) {
//				drawRect(texture, index[0][1][0], index[0][1][1]);
//			}
//			else if (p_forWard == bottom) {
//				drawRect(texture, index[3][1][0], index[3][1][1]);
//			}
//			else if (p_forWard == left) {
//				drawRect(texture, index[1][1][0], index[1][1][1]);
//			}
//			else if (p_forWard == right) {
//				drawRect(texture, index[2][1][0], index[2][1][1]);
//			}
//			isStop = true;
//
//		}
//		count3 = count2;
//	}
//	if (count == step * 3) {
//		count = 0;
//	}
//}