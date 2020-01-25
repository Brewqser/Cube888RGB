#include "PL9823.h"
#include <stdlib.h>

struct Tail
{
	int x;
	int y;
	int z;
	int color;
} tail;

struct Tail tailTable[4];
struct Tail aviable[6];
int av = 0;

int o[3][3][3];

void preset()
{
	tailTable[0].x=2;
	tailTable[0].y=1;
	tailTable[0].z=1;
	tailTable[0].color=0x00000f;
	o[2][1][1] = 1;
	
	tailTable[1].x=2;
	tailTable[1].y=2;
	tailTable[1].z=1;
	tailTable[1].color=0x000f00;
	o[2][2][1] = 1;
	
	tailTable[2].x=2;
	tailTable[2].y=1;
	tailTable[2].z=2;
	tailTable[2].color=0x0f0000;
	o[2][1][2] = 1;
	
	tailTable[3].x=2;
	tailTable[3].y=2;
	tailTable[3].z=2;
	tailTable[3].color=0x0f0f0f;
	o[2][2][2] = 1;
	
}

void update()
{
	clearAll();
	int i=0;
	for(i=0;i<4;i++)
	{
		setColor(tailTable[i].x * 2 - 1,tailTable[i].y * 2 - 1,tailTable[i].z * 2, tailTable[i].color);
		setColor(tailTable[i].x * 2    ,tailTable[i].y * 2 - 1,tailTable[i].z * 2    ,tailTable[i].color);
		setColor(tailTable[i].x * 2 - 1,tailTable[i].y * 2    ,tailTable[i].z * 2    ,tailTable[i].color);
		setColor(tailTable[i].x * 2    ,tailTable[i].y * 2    ,tailTable[i].z * 2    ,tailTable[i].color);
		setColor(tailTable[i].x * 2 - 1,tailTable[i].y * 2 - 1,tailTable[i].z * 2 - 1,tailTable[i].color);
		setColor(tailTable[i].x * 2    ,tailTable[i].y * 2 - 1,tailTable[i].z * 2 - 1,tailTable[i].color);
		setColor(tailTable[i].x * 2 - 1,tailTable[i].y * 2    ,tailTable[i].z * 2 - 1,tailTable[i].color);
		setColor(tailTable[i].x * 2    ,tailTable[i].y * 2    ,tailTable[i].z * 2 - 1,tailTable[i].color);
	}
	updateLeds();
}

void getAviable(int n)
{
	av = 0;
	
	if(tailTable[n].x - 1 >= 1 && o[tailTable[n].x - 1][tailTable[n].y][tailTable[n].z] == 0) 
	{
		aviable[av].x=tailTable[n].x - 1;
		aviable[av].y=tailTable[n].y;
		aviable[av].z=tailTable[n].z;
		av++;
	}
	
	if(tailTable[n].x + 1 <= 2 && o[tailTable[n].x + 1][tailTable[n].y][tailTable[n].z] == 0) 
	{
		aviable[av].x=tailTable[n].x + 1;
		aviable[av].y=tailTable[n].y;
		aviable[av].z=tailTable[n].z;
		av++;
	}
	
	if(tailTable[n].y - 1 >= 1 && o[tailTable[n].x][tailTable[n].y-1][tailTable[n].z] == 0) 
	{
		aviable[av].x=tailTable[n].x;
		aviable[av].y=tailTable[n].y - 1;
		aviable[av].z=tailTable[n].z;
		av++;
	}
	
	if(tailTable[n].y + 1 <= 2 && o[tailTable[n].x][tailTable[n].y + 1][tailTable[n].z] == 0) 
	{
		aviable[av].x=tailTable[n].x;
		aviable[av].y=tailTable[n].y + 1;
		aviable[av].z=tailTable[n].z;
		av++;
	}
	
	if(tailTable[n].z - 1 >= 1 && o[tailTable[n].x][tailTable[n].y][tailTable[n].z-1] == 0) 
	{
		aviable[av].x=tailTable[n].x;
		aviable[av].y=tailTable[n].y;
		aviable[av].z=tailTable[n].z- 1;
		av++;
	}
	
	if(tailTable[n].z + 1 <= 2 && o[tailTable[n].x][tailTable[n].y][tailTable[n].z + 1] == 0) 
	{
		aviable[av].x=tailTable[n].x;
		aviable[av].y=tailTable[n].y;
		aviable[av].z=tailTable[n].z + 1;
		av++;
	}
}


void move(int n)
{
	int tmp = 0;
	if (av != 0)
	{
		tmp = rand() % av;
		
		o[tailTable[n].x][tailTable[n].y][tailTable[n].z] = 0;
		
		if(tailTable[n].x > aviable[tmp].x)
		{
			clear(tailTable[n].x * 2, tailTable[n].y * 2, tailTable[n].z * 2);
			clear(tailTable[n].x * 2, tailTable[n].y * 2 - 1, tailTable[n].z * 2);
			clear(tailTable[n].x * 2, tailTable[n].y * 2, tailTable[n].z * 2 - 1);
			clear(tailTable[n].x * 2, tailTable[n].y * 2 - 1, tailTable[n].z * 2 - 1);
			setColor(aviable[tmp].x * 2, aviable[tmp].y * 2, aviable[tmp].z * 2, tailTable[n].color);
			setColor(aviable[tmp].x * 2, aviable[tmp].y * 2 - 1, aviable[tmp].z * 2, tailTable[n].color);
			setColor(aviable[tmp].x * 2, aviable[tmp].y * 2, aviable[tmp].z * 2 - 1, tailTable[n].color);
			setColor(aviable[tmp].x * 2, aviable[tmp].y * 2 - 1, aviable[tmp].z * 2 - 1, tailTable[n].color);
			updateLeds();
			delay(5000000);
		}
		
		if(tailTable[n].x < aviable[tmp].x)
		{
			clear(tailTable[n].x * 2 - 1, tailTable[n].y * 2, tailTable[n].z * 2);
			clear(tailTable[n].x * 2 - 1, tailTable[n].y * 2 - 1, tailTable[n].z * 2);
			clear(tailTable[n].x * 2 - 1, tailTable[n].y * 2, tailTable[n].z * 2 - 1);
			clear(tailTable[n].x * 2 - 1, tailTable[n].y * 2 - 1, tailTable[n].z * 2 - 1);
			setColor(aviable[tmp].x * 2 - 1, aviable[tmp].y * 2, aviable[tmp].z * 2, tailTable[n].color);
			setColor(aviable[tmp].x * 2 - 1, aviable[tmp].y * 2 - 1, aviable[tmp].z * 2, tailTable[n].color);
			setColor(aviable[tmp].x * 2 - 1, aviable[tmp].y * 2, aviable[tmp].z * 2 - 1, tailTable[n].color);
			setColor(aviable[tmp].x * 2 - 1, aviable[tmp].y * 2 - 1, aviable[tmp].z * 2 - 1, tailTable[n].color);
			updateLeds();
			delay(5000000);
		}

		
		if(tailTable[n].y > aviable[tmp].y)
		{
			clear(tailTable[n].x * 2, tailTable[n].y * 2, tailTable[n].z * 2);
			clear(tailTable[n].x * 2 - 1, tailTable[n].y * 2, tailTable[n].z * 2);
			clear(tailTable[n].x * 2, tailTable[n].y * 2, tailTable[n].z * 2 - 1);
			clear(tailTable[n].x * 2 - 1, tailTable[n].y * 2, tailTable[n].z * 2 - 1);
			setColor(aviable[tmp].x * 2, aviable[tmp].y * 2, aviable[tmp].z * 2, tailTable[n].color);
			setColor(aviable[tmp].x * 2 - 1, aviable[tmp].y * 2, aviable[tmp].z * 2, tailTable[n].color);
			setColor(aviable[tmp].x * 2, aviable[tmp].y * 2, aviable[tmp].z * 2 - 1, tailTable[n].color);
			setColor(aviable[tmp].x * 2 - 1, aviable[tmp].y * 2, aviable[tmp].z * 2 - 1, tailTable[n].color);
			updateLeds();
			delay(5000000);
		}
		
		if(tailTable[n].y < aviable[tmp].y)
		{
			clear(tailTable[n].x * 2    , tailTable[n].y * 2 - 1   , tailTable[n].z * 2);
			clear(tailTable[n].x * 2 - 1, tailTable[n].y * 2 - 1   , tailTable[n].z * 2);
			clear(tailTable[n].x * 2    , tailTable[n].y * 2 - 1   , tailTable[n].z * 2 - 1);
			clear(tailTable[n].x * 2 - 1, tailTable[n].y * 2 - 1   , tailTable[n].z * 2 - 1);
			setColor(aviable[tmp].x * 2    , aviable[tmp].y * 2 - 1, aviable[tmp].z * 2, tailTable[n].color);
			setColor(aviable[tmp].x * 2 - 1, aviable[tmp].y * 2 - 1, aviable[tmp].z * 2, tailTable[n].color);
			setColor(aviable[tmp].x * 2    , aviable[tmp].y * 2 - 1, aviable[tmp].z * 2 - 1, tailTable[n].color);
			setColor(aviable[tmp].x * 2 - 1, aviable[tmp].y * 2 - 1, aviable[tmp].z * 2 - 1, tailTable[n].color);
			updateLeds();
			delay(5000000);
		}
		
		if(tailTable[n].z > aviable[tmp].z)
		{
			clear(tailTable[n].x * 2, tailTable[n].y * 2, tailTable[n].z * 2);
			clear(tailTable[n].x * 2 - 1, tailTable[n].y * 2, tailTable[n].z * 2);
			clear(tailTable[n].x * 2, tailTable[n].y * 2 - 1, tailTable[n].z * 2);
			clear(tailTable[n].x * 2 - 1, tailTable[n].y * 2 - 1, tailTable[n].z * 2);
			setColor(aviable[tmp].x * 2, aviable[tmp].y * 2, aviable[tmp].z * 2, tailTable[n].color);
			setColor(aviable[tmp].x * 2 - 1, aviable[tmp].y * 2, aviable[tmp].z * 2, tailTable[n].color);
			setColor(aviable[tmp].x * 2, aviable[tmp].y * 2 - 1, aviable[tmp].z * 2, tailTable[n].color);
			setColor(aviable[tmp].x * 2 - 1, aviable[tmp].y * 2 - 1, aviable[tmp].z * 2, tailTable[n].color);
			
			updateLeds();
			delay(5000000);
		}
		
		if(tailTable[n].z < aviable[tmp].z)
		{
			clear(tailTable[n].x * 2, tailTable[n].y * 2, tailTable[n].z * 2 - 1);
			clear(tailTable[n].x * 2 - 1, tailTable[n].y * 2, tailTable[n].z * 2 - 1);
			clear(tailTable[n].x * 2, tailTable[n].y * 2 - 1, tailTable[n].z * 2 - 1);
			clear(tailTable[n].x * 2 - 1, tailTable[n].y * 2 - 1, tailTable[n].z * 2 - 1);
			setColor(aviable[tmp].x * 2, aviable[tmp].y * 2, aviable[tmp].z * 2 - 1, tailTable[n].color);
			setColor(aviable[tmp].x * 2 - 1, aviable[tmp].y * 2, aviable[tmp].z * 2 - 1, tailTable[n].color);
			setColor(aviable[tmp].x * 2, aviable[tmp].y * 2 - 1, aviable[tmp].z * 2 - 1, tailTable[n].color);
			setColor(aviable[tmp].x * 2 - 1, aviable[tmp].y * 2 - 1, aviable[tmp].z * 2 - 1, tailTable[n].color);
			
			updateLeds();
			delay(5000000);
		}
		
		tailTable[n].x = aviable[tmp].x;
		tailTable[n].y = aviable[tmp].y;
		tailTable[n].z = aviable[tmp].z;
		o[tailTable[n].x][tailTable[n].y][tailTable[n].z] = 1;
	}
}

int main (void) 
{
	initPL9823();
	
	int tmp;
	
	preset();
	update();
	delay(5000000);

	
	while(1)
	{
		tmp = rand() % 4;
		getAviable(tmp);
		move(tmp);
		update();
		delay(5000000);
	}
}
