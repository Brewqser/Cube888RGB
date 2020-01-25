#include "PL9823.h"
#include <stdlib.h>
#include "tsi.h"

struct RGB
{
	int r;
	int g;
	int b;
} LED;

struct RGB colorTable[Xsize][Ysize][Zsize];

void blink()
{
	clearAll();
	int i;
	int j;
	int k;
	for (i=1;i<=Xsize;i++)
	{
		for (j=1;j<=Ysize;j++)
		{
			for (k=1;k<=Zsize;k++)
			{
				setRGB(i,j,k,colorTable[i-1][j-1][k-1].r,colorTable[i-1][j-1][k-1].g,colorTable[i-1][j-1][k-1].b);
			}
		}
	}
	updateLeds();
}

void dim()
{
	int i;
	int j;
	int k;
	for (i=1;i<=Xsize;i++)
	{
		for (j=1;j<=Ysize;j++)
		{
			for (k=1;k<=Zsize;k++)
			{
				colorTable[i-1][j-1][k-1].r /= 2;
				colorTable[i-1][j-1][k-1].g /= 2;
				colorTable[i-1][j-1][k-1].b /= 2;
			}
		}
	}
}

int main (void) 
{
	initPL9823();
	TSI_Init();
	
	int i;
	int j;
	int k;
	int z;
	int scaler = 16;
	int blinksPerFrame = 5;
	int slider;
	int pressed = 0;
	int del = 1000000;
	
	while(1)
	{
		slider = TSI_ReadSlider();
		
		if(slider!=0)
		{
			
			if(pressed == 0)
			{
				if(slider<=50)
				{
					scaler+=32;
					if(scaler > 80) scaler = 16;
				}
				if(slider>50)
				{
					del += 1000000;
					if(del > 3000000) del = 1000000;
				}
			}
			pressed = 1;
		}
		else pressed = 0;
		
		for(z = 0; z < blinksPerFrame;z++)
		{
			if(	rand()%100 < 90) // 90% chanse to light up
			{
				i = rand()%Xsize;
				j = rand()%Ysize;
				k = rand()%Zsize;
				LED.r = rand()%scaler;
				LED.g = rand()%scaler;
				LED.b = rand()%scaler;
				colorTable[i][j][k] = LED;
			}
		}
		
		blink(); // update leds 
		
		dim(); // make blink effect;
		
		delay(del);
		
	}
	
}
