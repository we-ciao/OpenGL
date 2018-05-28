#pragma once

#include "BmpLoader.h"


const int MAZEROW = 17;
const int MAZECOL = 29;
const int CELLWIDTH = 5;
const int CELLHEIGHT = CELLWIDTH;



// Maze

//ö�� 
enum CellType {
	normal = 0, brick = 1, boom = 2, obstacle = 3, explosion = 4,						//3�ϰ��0�յأ�1 ש�飬2 ը�� ,4 ��ը
	monsterUp = 41, monsterRight = 42, monsterDown = 43, monsterLeft = 44,			//4��ͷΪ��������������ĸ�״̬
	playerUp = 91, playerRight = 92, playerDown = 93, playerLeft = 94,	//9��ͷΪ��ҵ����������ĸ�״̬
	playerWboomUp = 95, playerWboomRight = 96, playerWboomDown = 97, playerWboomLeft = 98,	//ը���������ͬһλ��
};

class Maze
{
public:
	CBmpLoader * Texture;
	Maze();
	virtual ~Maze();
	void DrawMaze();
	const static int WINDOWWIDTH = 950;//��Ļ���
	const static int WINDOWHEIGHT = 640;//��Ļ�߶�
	void setCellVal(int x, int y, int val);		//���û÷�ֵ
	int getCellVal(int x, int y);				//�õ��÷�ֵ

protected:
	int	 ppMaze[MAZEROW][MAZECOL];

private:
	void initMaze();//��ʼ���Թ�
	void createBrick();//�������ש��
	void createMonster();//������ɹ���
	void drawCell(CPoint p, int type);//���Ʒ���, ��pλ�û���type����
};


