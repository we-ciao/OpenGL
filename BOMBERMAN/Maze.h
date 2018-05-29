#pragma once

#include "BmpLoader.h"

const int MAZEROW = 17;
const int MAZECOL = 29;
const int CELLWIDTH = 5;
const int CELLHEIGHT = CELLWIDTH;



// Maze

//枚举 
enum CellType {
	normal = 0, brick = 1, boom = 2, obstacle = 3, explosion = 4,				//3障碍物，0空地，1 砖块，2 炸弹 ,4 爆炸
	reward = 5,	//	道具
	monsterUp = 41, monsterRight = 42, monsterDown = 43, monsterLeft = 44,			//4开头为怪物的上下左右四个状态
	playerUp = 91, playerRight = 92, playerDown = 93, playerLeft = 94,			//9开头为玩家的上下左右四个状态
	playerWboomUp = 95, playerWboomRight = 96, playerWboomDown = 97, playerWboomLeft = 98,	//炸弹和玩家在同一位置
};

class Bomb;

class Maze
{
public:
	CBmpLoader * Texture;
	Maze();
	virtual ~Maze();
	void DrawMaze();
	const static int WINDOWWIDTH = 950;//屏幕宽度
	const static int WINDOWHEIGHT = 640;//屏幕高度
	void setCellVal(int x, int y, int val);		//设置幻方值
	int getCellVal(int x, int y);				//得到幻方值
	
protected:
	int	 ppMaze[MAZEROW][MAZECOL];

private:
	void initMaze();//初始化迷宫
	void createBrick();//随机生成砖块
	void createMonster();//随机生成怪物
	void drawCell(CPoint p, int type);//绘制方格, 在p位置绘制type方格
};


