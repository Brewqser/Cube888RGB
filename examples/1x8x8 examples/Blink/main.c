#include "PL9823.h"
#include <stdlib.h>

struct RGB
{
	int r;
	int g;
	int b;
} LED;

struct RGB colorTable[Ysize][Zsize];

void blink()
{
	clearAll();
	int i;
	int j;
	for (i=1;i<=Ysize;i++)
	{
		for (j=1;j<=Zsize;j++)
		{
			setRGB(1,i,j,colorTable[i-1][j-1].r,colorTable[i-1][j-1].g,colorTable[i-1][j-1].b);
		}
	}
	updateLeds();
}

void dim()
{
	int i;
	int j;
	for (i=1;i<=Ysize;i++)
	{
		for (j=1;j<=Zsize;j++)
		{
			colorTable[i-1][j-1].r /= 2;
			colorTable[i-1][j-1].g /= 2;
			colorTable[i-1][j-1].b /= 2;
		}
	}
}

int main (void) 
{
	initPL9823();
	int i;
	int j;
	int k;
	int scaler = 16;
	int blinksPerFrame = 10;
	
	while(1)
	{
		for(k = 0; k < blinksPerFrame;k++)
		{
			if(	rand()%100 < 90)
			{
				i = rand()%Ysize;
				j = rand()%Zsize;
				LED.r = rand()%scaler;
				LED.g = rand()%scaler;
				LED.b = rand()%scaler;
				colorTable[i][j] = LED;
			}
		}
		
		blink(); // update leds 
		
		dim(); // make blink effect;
		
		delay(1000000);
	}
}