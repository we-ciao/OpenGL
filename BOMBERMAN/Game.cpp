
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

//����ը��
void Game::manageBomb()
{
	std::list<Boom*>::iterator	it;

	for (it = boomlist.begin(); boomlist.size() > 0 && it != boomlist.end();)
	{

		if ((*it)->timeOver(_time) == true)//�ж��Ƿ񵽴ﱬըʱ��
		{
			(*it)->explose(&maze);
			//this->getPlayerById((*it)->getId())->getSkills().delBomb();�жϽ�ɫ�ͷ�ը�������ֵ
			delete *it;
			it = boomlist.erase(it);
		}
		else
			++it;
	}
}