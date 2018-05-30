
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
	_time++;		//��ʱ��ʼ

	manageBomb();
	maze.DrawMaze();
	manageMonster();
}


//������ɹ���
void Game::createMonster()
{
	srand((unsigned)time(NULL));
	for (int i = 2; i < MAZEROW; i++)
	{
		for (int j = 2; j < MAZECOL; j++) {
			if (rand() % 20 < 1 && maze.getCellVal(i, j) == normal) {
				maze.setCellVal(i, j, monsterDown);
				Monster* monster = new Monster(i,j);		//����ը��
				monsterlist.push_back(monster);				//��������
			}
		}
	}
}

//�������
void Game::manageMonster()
{

	std::list<Monster*>::iterator	it;

	for (it = monsterlist.begin(); monsterlist.size() > 0 && it != monsterlist.end();)
	{

		if ((*it)->alive == true)//�ж��Ƿ񵽴ﱬըʱ��
		{

		}
		else
			++it;
	}
}

//����ը��
void Game::manageBomb()
{
	//��ը֮�� ��Ϊƽ��
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