// Maze.cpp : implementation file
//

#include "stdafx.h"
#include "BOMBERMAN.h"
#include "Maze.h"
#include "Monster.h"
#include "time.h"
#include "windows.h"

#include"gl/gl.h"
#include"gl/glu.h"


// Maze

Maze::Maze()
{
	initMaze();
}

Maze::~Maze()
{
	
}


void DrawBox(float r)
{
	/** 开始绘制四边形 */
	glBegin(GL_QUADS);
	/// 前侧面
	glNormal3f(0.0f, 0.0f, 1.0f);								/**< 指定法线指向观察者 */
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-r, -r, r);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(r, -r, r);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(r, r, r);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-r, r, r);
	/// 后侧面
	glNormal3f(0.0f, 0.0f, -1.0f);								/**< 指定法线背向观察者 */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-r, -r, -r);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-r, r, -r);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(r, r, -r);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(r, -r, -r);
	/// 顶面
	glNormal3f(0.0f, 1.0f, 0.0f);								/**< 指定法线向上 */
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-r, r, -r);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-r, r, r);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(r, r, r);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(r, r, -r);
	/// 底面
	glNormal3f(0.0f, -1.0f, 0.0f);								/**< 指定法线朝下 */
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-r, -r, -r);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(r, -r, -r);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(r, -r, r);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-r, -r, r);
	/// 右侧面
	glNormal3f(1.0f, 0.0f, 0.0f);								/**< 指定法线朝右 */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(r, -r, -r);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(r, r, -r);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(r, r, r);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(r, -r, r);
	/// 左侧面
	glNormal3f(-1.0f, 0.0f, 0.0f);								/**< 指定法线朝左 */
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-r, -r, -r);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-r, -r, r);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-r, r, r);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-r, r, -r);
	glEnd();
}

//绘制迷宫
void Maze::DrawMaze(void)
{

	//设置清屏颜色为黑色
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//清除颜色缓冲区和深度缓冲区
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0, 0, -100);
	glRotatef(180, 1, 0, 0);
	glTranslatef(-WINDOWWIDTH / 13, -WINDOWHEIGHT / 15, 0);

	CPoint p;
	for (int i = 0; i < MAZEROW; i++)
	{
		for (int j = 0; j < MAZECOL; j++) {

			p.x = j * CELLWIDTH;
			p.y = i * CELLHEIGHT;
			drawCell(p, ppMaze[i][j]);

		}
	}
	glFlush();
	SwapBuffers(wglGetCurrentDC());
}



//初始化迷宫
void Maze::initMaze() {
	int i, j;
	memset(ppMaze, normal, sizeof(ppMaze));//0代表可以通过的路径
	for (i = 1; i < MAZEROW; i += 2)
	{
		for (j = 1; j < MAZECOL; j += 2) {

			ppMaze[i][j] = obstacle;
		}
	}
	ppMaze[0][0] = playerDown;//设置玩家
	createBrick();//随机生成砖块
	/*HANDLE hThread = CreateThread(NULL, 0, createMonster, NULL, 0, NULL);
	CloseHandle(hThread);*/
	//createMonster();//随机生成怪物
}

//随机生成砖块
void Maze::createBrick()
{

}
//随机生成怪物
void Maze::createMonster()
{
	srand((unsigned)time(0));
	Monster monster(rand()%MAZEROW,rand()%MAZECOL);
	setCellVal(monster.m_x,monster.m_y, monsterUp);
}
//绘制方格, 在p位置绘制type方格
void Maze::drawCell(CPoint p, int type)
{
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, Texture[type].ID);
	if (type == explosion)
	{
		glColor3f(0,0,0);
	}
	glBegin(GL_QUADS);  // OpenGL绘制直线命令
	glTexCoord2f(0.0f, 1.0f); glVertex2d(p.x, p.y);
	glTexCoord2f(1.0f, 1.0f); glVertex2d(p.x + CELLWIDTH, p.y);
	glTexCoord2f(1.0f, 0.0f); glVertex2d(p.x + CELLWIDTH, p.y + CELLHEIGHT);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(p.x, p.y + CELLHEIGHT);
	glEnd();

	glPopMatrix();
}

//设置幻方值
void Maze::setCellVal(int x, int y, int val)
{
	ppMaze[x][y] = val;
}

//得到幻方值
int Maze::getCellVal(int x, int y)
{
	return ppMaze[x][y];
}