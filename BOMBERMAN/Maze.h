#pragma once




const int MAZEROW = 30;
const int MAZECOL = 50;
const int CELLWIDTH = 5;
const int CELLHEIGHT = CELLWIDTH;



// Maze

//枚举 
enum CellType{
	obstacle = -1, normal = 0,brick = 1 ,boom = 2,							//-1障碍物，0空地，1 砖块，2 炸弹
	monterUp = 41,monterRight = 42,monterDown = 43,monterLeft = 44,			//4开头为怪物的上下左右四个状态
	playerUp = 91, playerRight = 92,playerDown = 93,playerLeft = 94,	//9开头为玩家的上下左右四个状态
};

class Maze 
{
public:
	Maze();
	virtual ~Maze();
	void DrawMaze();
const static	 int WINDOWWIDTH=960 ;
const static int WINDOWHEIGHT =640;
	

protected:
	int ppMaze[MAZEROW][MAZECOL];

private:
	void initMaze();//初始化迷宫
	void createBrick();//随机生成砖块
	void createMonster();//随机生成怪物
	void drawCell(CPoint p,int type);//绘制方格, 在p位置绘制type方格
};


