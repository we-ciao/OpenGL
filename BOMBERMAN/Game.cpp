
#include "stdafx.h"
#include "Game.h"
#include "Font.h"
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
	char string[] = "YOU LOSE!";
	GLFont font;
	if (!maze.gameOver)
	{
		maze.DrawMaze();
	}
	else
	{
		//设置清屏颜色为黑色
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		//清除颜色缓冲区和深度缓冲区
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
			glPopMatrix();
			glPushAttrib(GL_CURRENT_BIT);
			glColor3f(1.0, 1.0, 1.0);
			font.PrintText(string, 0, 0);
			glPopAttrib();
			glFlush();
			SwapBuffers(wglGetCurrentDC());
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