
#include "stdafx.h"
#include "BOMBERMAN.h"
#include "Game.h"
#include "Maze.h"
#include "Boom.h"

// Maze

Game::Game()
{
	player.maze = &maze;
	player.boomlist = &boomlist;
}

Game::~Game()
{

}

//管理炸弹
void Game::manageBomb()
{
	for (int i = 0; i < MAZEROW; i++)
	{
		for (int j = 0; j < MAZECOL; j++) {
			if (maze.getCellVal(i, j) == explosion)
				maze.setCellVal(i,j,normal);
		}
	}

	std::list<Boom*>::iterator	it;

	for (it = boomlist.begin(); boomlist.size() > 0 && it != boomlist.end();)
	{

		if ((*it)->timeOver(_time) == true)//判断是否到达爆炸时间
		{
			(*it)->explose(&maze);
			//this->getPlayerById((*it)->getId())->getSkills().delBomb();判断角色释放炸弹的最大值
			delete *it;
			it = boomlist.erase(it);
		}
		else
			++it;
	}
}