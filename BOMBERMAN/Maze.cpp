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
	/** ��ʼ�����ı��� */
	glBegin(GL_QUADS);
	/// ǰ����
	glNormal3f(0.0f, 0.0f, 1.0f);								/**< ָ������ָ��۲��� */
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-r, -r, r);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(r, -r, r);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(r, r, r);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-r, r, r);
	/// �����
	glNormal3f(0.0f, 0.0f, -1.0f);								/**< ָ�����߱���۲��� */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-r, -r, -r);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-r, r, -r);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(r, r, -r);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(r, -r, -r);
	/// ����
	glNormal3f(0.0f, 1.0f, 0.0f);								/**< ָ���������� */
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-r, r, -r);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-r, r, r);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(r, r, r);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(r, r, -r);
	/// ����
	glNormal3f(0.0f, -1.0f, 0.0f);								/**< ָ�����߳��� */
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-r, -r, -r);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(r, -r, -r);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(r, -r, r);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-r, -r, r);
	/// �Ҳ���
	glNormal3f(1.0f, 0.0f, 0.0f);								/**< ָ�����߳��� */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(r, -r, -r);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(r, r, -r);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(r, r, r);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(r, -r, r);
	/// �����
	glNormal3f(-1.0f, 0.0f, 0.0f);								/**< ָ�����߳��� */
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-r, -r, -r);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-r, -r, r);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-r, r, r);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-r, r, -r);
	glEnd();
}

//�����Թ�
void Maze::DrawMaze(void)
{

	//����������ɫΪ��ɫ
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//�����ɫ����������Ȼ�����
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



//��ʼ���Թ�
void Maze::initMaze() {
	int i, j;
	memset(ppMaze, normal, sizeof(ppMaze));//0�������ͨ����·��
	for (i = 1; i < MAZEROW; i += 2)
	{
		for (j = 1; j < MAZECOL; j += 2) {

			ppMaze[i][j] = obstacle;
		}
	}
	ppMaze[0][0] = playerDown;//�������
	createBrick();//�������ש��
	/*HANDLE hThread = CreateThread(NULL, 0, createMonster, NULL, 0, NULL);
	CloseHandle(hThread);*/
	//createMonster();//������ɹ���
}

//�������ש��
void Maze::createBrick()
{

}
//������ɹ���
void Maze::createMonster()
{
	srand((unsigned)time(0));
	Monster monster(rand()%MAZEROW,rand()%MAZECOL);
	setCellVal(monster.m_x,monster.m_y, monsterUp);
}
//���Ʒ���, ��pλ�û���type����
void Maze::drawCell(CPoint p, int type)
{
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, Texture[type].ID);
	if (type == explosion)
	{
		glColor3f(0,0,0);
	}
	glBegin(GL_QUADS);  // OpenGL����ֱ������
	glTexCoord2f(0.0f, 1.0f); glVertex2d(p.x, p.y);
	glTexCoord2f(1.0f, 1.0f); glVertex2d(p.x + CELLWIDTH, p.y);
	glTexCoord2f(1.0f, 0.0f); glVertex2d(p.x + CELLWIDTH, p.y + CELLHEIGHT);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(p.x, p.y + CELLHEIGHT);
	glEnd();

	glPopMatrix();
}

//���û÷�ֵ
void Maze::setCellVal(int x, int y, int val)
{
	ppMaze[x][y] = val;
}

//�õ��÷�ֵ
int Maze::getCellVal(int x, int y)
{
	return ppMaze[x][y];
}