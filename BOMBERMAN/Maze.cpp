// Maze.cpp : implementation file
//

#include "stdafx.h"
#include "BOMBERMAN.h"
#include "Maze.h"

#include"gl/gl.h"
#include"gl/glu.h"


// Maze

Maze::Maze()
{

}

Maze::~Maze()
{
}


void Maze::DrawScence(void)
{

	//设置清屏颜色为黑色
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	//清除颜色缓冲区和深度缓冲区
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0,0,-6);
	
	glFinish();
	SwapBuffers(wglGetCurrentDC());
	//for (int i=0;i<MAZEROW;i++)
	//{
	//	for(int j=0;j<MAZECOL;j++){
	//		CPoint p;
	//		p.x = i*CELLWIDTH+12;

	//		
	//			drawCell()
	//		
	//	}
	//}
	
}



//初始化迷宫
void Maze::initMaze(){
	int i,j;
	memset(ppMaze,normal,sizeof(ppMaze));//0代表可以通过的路径
	for (i=1;i<MAZEROW;i+=2)
	{
		for(j=1;j<MAZECOL;j+=2){
		
				ppMaze[i][j]=obstacle;
		}
	}
	ppMaze[0][0] = playerDown;//设置玩家
	createBrick();//随机生成砖块
	createMonster();//随机生成怪物
}

//随机生成砖块
void Maze::createBrick()
{

}
//随机生成怪物
void Maze::createMonster()
{

}
//绘制方格, 在p位置绘制type方格
void Maze::drawCell(CPoint p,int type)
{
	glBegin(GL_QUADS);  // OpenGL绘制直线命令
	glColor3f(1.0, 0.0, 0.0); // 设置当前颜色为红色

	glVertex3f(-1.0, 0.0,0.0);
	glVertex3f(-1.0, 1.0,0.0);
	glVertex3f(1.0, 1.0,0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glEnd();
}