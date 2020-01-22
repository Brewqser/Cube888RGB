#include "blink.h"

void blinkOnce(void)
{
	int i;
	int j;
	clearAll();
	for (i=1;i<=Ysize;i++)
	{
		for (j=1;j<=Zsize;j++)
		{
			setRGB(1,i,j,blinkColorTable[i-1][j-1].r,blinkColorTable[i-1][j-1].g,blinkColorTable[i-1][j-1].b);
		}
	}
	updateLeds();
}

void dim(void)
{
	int i;
	int j;
	for (i=1;i<=Ysize;i++)
	{
		for (j=1;j<=Zsize;j++)
		{
			blinkColorTable[i-1][j-1].r /= 2;
			blinkColorTable[i-1][j-1].g /= 2;
			blinkColorTable[i-1][j-1].b /= 2;
		}
	}
}

void prepareBlink(void)
{
	int i;
	int j;
	
	scalerB = 16;
	blinksPerFrameB = 10;
	
	LED.r = 0;
	LED.g = 0;
	LED.b = 0;
	
	for (i=1;i<=Ysize;i++)
	{
		for (j=1;j<=Zsize;j++)
		{
			blinkColorTable[i][j] = LED;
		}
	}
}

void stepBlink(void)
{
	int i;
	int j;
	int k;
	for(k = 0; k < blinksPerFrameB;k++)
	{
		if(	rand()%100 < 90)
		{
			i = rand()%Ysize;
			j = rand()%Zsize;
			LED.r = rand()%scalerB;
			LED.g = rand()%scalerB;
			LED.b = rand()%scalerB;
			blinkColorTable[i][j] = LED;
		}
	}
	
	blinkOnce(); // update leds 
	
	dim(); // make blink effect;
}
