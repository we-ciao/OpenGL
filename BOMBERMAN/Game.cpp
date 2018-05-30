
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
		//����������ɫΪ��ɫ
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		//�����ɫ����������Ȼ�����
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