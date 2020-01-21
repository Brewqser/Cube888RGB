#include "PL9823.h"
#include <stdlib.h>

struct Tail
{
	int x;
	int y;
	int color;
} tail;

struct Tail tailTable[8];
struct Tail aviable[4];
int av = 0;

int o[5][5];

void preset()
{
	tailTable[0].x=1;
	tailTable[0].y=1;
	tailTable[0].color=0x0000ff;
	o[1][1] = 1;
	
	tailTable[1].x=1;
	tailTable[1].y=2;
	tailTable[1].color=0x00ff00;
	o[1][2] = 1;
	
	tailTable[2].x=1;
	tailTable[2].y=3;
	tailTable[2].color=0xff0000;
	o[1][3] = 1;
	
	tailTable[3].x=1;
	tailTable[3].y=4;
	tailTable[3].color=0x00ffff;
	o[1][4] = 1;
	
	tailTable[4].x=2;
	tailTable[4].y=1;
	tailTable[4].color=0xffff00;
	o[2][1] = 1;
	
	tailTable[5].x=2;
	tailTable[5].y=2;
	tailTable[5].color=0xff00ff;
	o[2][2] = 1;
	
	tailTable[6].x=2;
	tailTable[6].y=3;
	tailTable[6].color=0xffffff;
	o[2][3] = 1;
	
	tailTable[7].x=2;
	tailTable[7].y=4;
	tailTable[7].color=0x3216ff;
	o[2][4] = 1;
}

void update()
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

void getAviable(int n)
{
	av = 0;
	
	if(tailTable[n].x - 1 >= 1 && o[tailTable[n].x - 1][tailTable[n].y] == 0) 
	{
		aviable[av].x=tailTable[n].x - 1;
		aviable[av].y=tailTable[n].y;
		av++;
	}
	
	if(tailTable[n].x + 1 <= 4 && o[tailTable[n].x + 1][tailTable[n].y] == 0) 
	{
		aviable[av].x=tailTable[n].x + 1;
		aviable[av].y=tailTable[n].y;
		av++;
	}
	
	if(tailTable[n].y - 1 >= 1 && o[tailTable[n].x][tailTable[n].y-1] == 0) 
	{
		aviable[av].x=tailTable[n].x;
		aviable[av].y=tailTable[n].y - 1;
		av++;
	}
	
	if(tailTable[n].y + 1 <= 4 && o[tailTable[n].x][tailTable[n].y + 1] == 0) 
	{
		aviable[av].x=tailTable[n].x;
		aviable[av].y=tailTable[n].y + 1;
		av++;
	}
}

void move(int n)
{
	int tmp = 0;
	if (av != 0)
	{
		tmp = rand() % av;
		o[tailTable[n].x][tailTable[n].y] = 0;
		tailTable[n].x = aviable[tmp].x;
		tailTable[n].y = aviable[tmp].y;
		o[tailTable[n].x][tailTable[n].y] = 1;
	}
}


int main (void) 
{
	initPL9823();
	preset();
	
	int tmp;
	
	while(1)
	{
		tmp = rand() % 8;
		getAviable(tmp);
		move(tmp);
		update();
		delay(2000000);
	}
}