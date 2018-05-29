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
	const static int WINDOWWIDTH = 950;//屏幕宽度
	const static int WINDOWHEIGHT = 640;//屏幕高度



	Maze maze;
	Player player;

	double	_time;//时间

	std::list<Boom*> boomlist;//炸弹队列
	void Game::manageBomb();//管理炸弹

protected:

};
