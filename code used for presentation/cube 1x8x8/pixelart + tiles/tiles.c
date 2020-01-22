#include "tiles.h"

void updateT()
{
	clearAll();
	int i=0;
	for(i=0;i<8;i++)
	{
		setColor(1,tailTable[i].x * 2 - 1,tailTable[i].y * 2 - 1,tailTable[i].color);
		setColor(1,tailTable[i].x * 2 ,tailTable[i].y * 2 - 1,tailTable[i].color);
		setColor(1,tailTable[i].x * 2 - 1,tailTable[i].y * 2,tailTable[i].color);
		setColor(1,tailTable[i].x * 2 ,tailTable[i].y * 2,tailTable[i].color);
	}
	updateLeds();
}

void getAviableT(int n)
{
	avT = 0;
	
	if(tailTable[n].x - 1 >= 1 && oT[tailTable[n].x - 1][tailTable[n].y] == 0) 
	{
		aviable[avT].x=tailTable[n].x - 1;
		aviable[avT].y=tailTable[n].y;
		avT++;
	}
	
	if(tailTable[n].x + 1 <= 4 && oT[tailTable[n].x + 1][tailTable[n].y] == 0) 
	{
		aviable[avT].x=tailTable[n].x + 1;
		aviable[avT].y=tailTable[n].y;
		avT++;
	}
	
	if(tailTable[n].y - 1 >= 1 && oT[tailTable[n].x][tailTable[n].y-1] == 0) 
	{
		aviable[avT].x=tailTable[n].x;
		aviable[avT].y=tailTable[n].y - 1;
		avT++;
	}
	
	if(tailTable[n].y + 1 <= 4 && oT[tailTable[n].x][tailTable[n].y + 1] == 0) 
	{
		aviable[avT].x=tailTable[n].x;
		aviable[avT].y=tailTable[n].y + 1;
		avT++;
	}
}

void move(int n, int del)
{
	int tmp = 0;
	if (avT != 0)
	{
		tmp = rand() % avT;
		oT[tailTable[n].x][tailTable[n].y] = 0;
		
		if(tailTable[n].x > aviable[tmp].x)
		{
			clear(1,tailTable[n].x * 2, tailTable[n].y * 2);
			clear(1,tailTable[n].x * 2, tailTable[n].y * 2 -1);
			setColor(1,aviable[tmp].x * 2, aviable[tmp].y * 2, tailTable[n].color);
			setColor(1,aviable[tmp].x * 2, aviable[tmp].y * 2 - 1,tailTable[n].color);
		}
		
		if(tailTable[n].x < aviable[tmp].x)
		{
			clear(1,tailTable[n].x * 2 - 1, tailTable[n].y * 2);
			clear(1,tailTable[n].x * 2 - 1, tailTable[n].y * 2 -1);
			setColor(1,aviable[tmp].x * 2 - 1, aviable[tmp].y * 2, tailTable[n].color);
			setColor(1,aviable[tmp].x * 2 - 1, aviable[tmp].y * 2 - 1,tailTable[n].color);
		}

		if(tailTable[n].y > aviable[tmp].y)
		{
			clear(1,tailTable[n].x * 2, tailTable[n].y * 2);
			clear(1,tailTable[n].x * 2 - 1, tailTable[n].y * 2);
			setColor(1,aviable[tmp].x * 2, aviable[tmp].y * 2, tailTable[n].color);
			setColor(1,aviable[tmp].x * 2 - 1, aviable[tmp].y * 2,tailTable[n].color);
		}
		
		if(tailTable[n].y < aviable[tmp].y)
		{
			clear(1,tailTable[n].x * 2, tailTable[n].y * 2 - 1);
			clear(1,tailTable[n].x * 2 - 1, tailTable[n].y * 2 - 1);
			setColor(1,aviable[tmp].x * 2, aviable[tmp].y * 2 - 1, tailTable[n].color);
			setColor(1,aviable[tmp].x * 2 - 1, aviable[tmp].y * 2- 1,tailTable[n].color);
		}
		updateLeds();
		delay(del);
		tailTable[n].x = aviable[tmp].x;
		tailTable[n].y = aviable[tmp].y;
		oT[tailTable[n].x][tailTable[n].y] = 1;
	}
}

void prepareTiles(void)
{
	int i;
	int j;
	for(i=1;i<=4;i++)
	{
		for (j=1;j<=4;j++)
			oT[i][j] = 0;
	}
	tailTable[0].x=1;
	tailTable[0].y=1;
	tailTable[0].color=0x0000ff;
	oT[1][1] = 1;
	
	tailTable[1].x=1;
	tailTable[1].y=2;
	tailTable[1].color=0x00ff00;
	oT[1][2] = 1;
	
	tailTable[2].x=1;
	tailTable[2].y=3;
	tailTable[2].color=0xff0000;
	oT[1][3] = 1;
	
	tailTable[3].x=1;
	tailTable[3].y=4;
	tailTable[3].color=0x00ffff;
	oT[1][4] = 1;
	
	tailTable[4].x=2;
	tailTable[4].y=1;
	tailTable[4].color=0xffff00;
	oT[2][1] = 1;
	
	tailTable[5].x=2;
	tailTable[5].y=2;
	tailTable[5].color=0xff00ff;
	oT[2][2] = 1;
	
	tailTable[6].x=2;
	tailTable[6].y=3;
	tailTable[6].color=0xffffff;
	oT[2][3] = 1;
	
	tailTable[7].x=2;
	tailTable[7].y=4;
	tailTable[7].color=0x3216ff;
	oT[2][4] = 1;
}

void stepTiles(int del)
{
	int tmp = rand() % 8;
	getAviableT(tmp);
	move(tmp,del);
	updateT();
}
