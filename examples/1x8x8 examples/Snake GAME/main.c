#include "PL9823.h"
#include <stdlib.h>
#include "buttons.h"

struct Part 
{
	int x;
	int y;
} part;

struct Part snake[70];
struct Part food;
int o[10][10];

struct Part aviable[70];
int av = 0;

int loose = 0;

int size = 3;

int direction = 0;
int newdir = 0;

void setFood()
{
	int i=0;
	int j=0;
	int tmp;
	av = 0;
	
	for(i=1;i<=Ysize;i++)
	{
		for(j=1;j<=Zsize;j++)
		{
			if(o[i][j] == 0)
			{
				aviable[av].x = i;
				aviable[av].y = j;
				av++;
			}
		}
	}
	
	tmp = rand()%av;
	
	food = aviable[tmp];
	
}

void preset()
{
	snake[0].x = 3;
	snake[0].y = 4;
	o[snake[0].x][snake[0].y] = 1;
	
	snake[1].x = 2;
	snake[1].y = 4;
	o[snake[1].x][snake[1].y] = 1;
	
	snake[2].x = 1;
	snake[2].y = 4;
	o[snake[2].x][snake[2].y] = 1;
	
	setFood();
	size = 3;
}

void update()
{
	clearAll();
	int i=0;
	
	for(i=0;i<size;i++)
	{
		if(snake[i].x != 0 && snake[i].y != 0) setColor(1,snake[i].x ,snake[i].y, 0x00ff00);
	}
	
	setColor(1,snake[0].x ,snake[0].y, 0x0000ff);
	
	setColor(1,food.x ,food.y, 0xff0000);
	
	updateLeds();
}

void checkDir()
{
	newdir = 0;
	
	if(!button1Read()) 
	{
		newdir = 2;
	}
	else if(!button3Read())
	{
		newdir = 1;
	}
}

void checkLoose()
{
	int i=0;
	for(i=1;i<size;i++)
	{
		if(snake[0].x == snake[i].x && snake[0].y == snake[i].y) loose = 1; 
	}
}

void move()
{
	int i=0;
	
	o[snake[size-1].x][snake[size-1].y] = 0;
	
	if(direction == 0)
	{
		for(i=size-1;i>=1;i--)
		{
			snake[i] = snake[i-1];
		}
		snake[0].x++;
		checkLoose();
		if(snake[0].x == Zsize + 1) snake[0].x = 1;
		
	}
	
	if(direction == 1)
	{
		for(i=size-1;i>=1;i--)
		{
			snake[i] = snake[i-1];
		}
		snake[0].y++;
		checkLoose();
		if(snake[0].y == Ysize + 1) snake[0].y = 1;
	}
	
	if(direction == 2)
	{
		for(i=size-1;i>=1;i--)
		{
			snake[i] = snake[i-1];
		}
		snake[0].x--;
		checkLoose();
		if(snake[0].x == 0) snake[0].x = Zsize;
	}
	
	if(direction == 3)
	{
		for(i=size-1;i>=1;i--)
		{
			snake[i] = snake[i-1];
		}
		snake[0].y--;
		checkLoose();
		if(snake[0].y == 0) snake[0].y = Ysize;
	}
	o[snake[0].x][snake[0].y] = 1;
}

void setDir()
{

	if(direction == 0)
	{
		if(newdir == 1)
		{
			direction = 3;
		}
		if(newdir == 2)
		{
			direction = 1;
		}
	}
	
	else if(direction == 1)
	{
		if(newdir == 1)
		{
			direction = 0;
		}
		if(newdir == 2)
		{
			direction = 2;
		}
	}
	
	else if(direction == 2)
	{
		if(newdir == 1)
		{
			direction = 1;
		}
		if(newdir == 2)
		{
			direction = 3;
		}
	}
	
	else if(direction == 3)
	{
		if(newdir == 1)
		{
			direction = 2;
		}
		if(newdir == 2)
		{
			direction = 0;
		}
	}
}

void checkFood()
{
	if(snake[0].x == food.x && snake[0].y == food.y) 
	{
		size++;
		setFood();
	}
}

int main (void) 
{
	initPL9823();
	buttonsInitialize();
	
	preset();
	
	while(!loose)
	{
		checkDir();
		setDir();
		move();
		checkFood();
		update();
		delay(5000000);
	}
}
