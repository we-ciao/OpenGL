#pragma once

#include "BmpLoader.h"
#include "Boom.h"
#include "Maze.h"
#include "Player.h"
#include <list>

class Game
{
public:
	Game();
	virtual ~Game();
	const static int WINDOWWIDTH = 950;//��Ļ���
	const static int WINDOWHEIGHT = 640;//��Ļ�߶�



	Maze maze;
	Player player;

	double	_time;//ʱ��

	std::list<Boom*> boomlist;//ը������
	void Game::manageBomb();//����ը��

protected:

};
