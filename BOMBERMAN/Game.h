#pragma once

#include "BmpLoader.h"
#include "Boom.h"
#include "Maze.h"
#include "Monster.h"
#include "Player.h"
#include "BOMBERMAN.h"
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
	void manageBomb();//����ը��
	void manageMonster();
	void draw();

protected:
	std::list<Boom*> boomlist;//ը������
	std::list<Monster*> monsterlist;//�������
	void createMonster();
};
