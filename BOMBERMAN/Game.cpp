
#include "stdafx.h"
#include "Game.h"

// Maze

Game::Game()
{

	//player = new Player(12, 96, -2.0f, -2.5f,0, index1, 0.15f);
	player.maze = &maze;
	player.boomlist = &boomlist;
}

Game::~Game()
{

}

void Game::draw()
{
	_time++;		//计时开始

	manageBomb();
	maze.DrawMaze();
	manageMonster();
}


//随机生成怪物
void Game::createMonster()
{
	srand((unsigned)time(NULL));
	for (int i = 2; i < MAZEROW; i++)
	{
		for (int j = 2; j < MAZECOL; j++) {
			if (rand() % 20 < 1 && maze.getCellVal(i, j) == normal) {
				maze.setCellVal(i, j, monsterDown);
				Monster* monster = new Monster(i,j);		//制造炸弹
				monsterlist.push_back(monster);				//放入链表
			}
		}
	}
}

//管理怪物
void Game::manageMonster()
{

	std::list<Monster*>::iterator	it;

	for (it = monsterlist.begin(); monsterlist.size() > 0 && it != monsterlist.end();)
	{

		if ((*it)->alive == true)//判断是否到达爆炸时间
		{

		}
		else
			++it;
	}
}

//管理炸弹
void Game::manageBomb()
{
	//爆炸之后 变为平地
	for (int i = 0; i < MAZEROW; i++)
	{
		for (int j = 0; j < MAZECOL; j++) {
			if (maze.getCellVal(i, j) == explosion)
				if (maze.getCellVal(i, j) != boom)
					maze.setCellVal(i, j, normal);
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