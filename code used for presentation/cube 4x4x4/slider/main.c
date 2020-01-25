#include "PL9823.h"
#include <stdlib.h>
#include "tsi.h"

int main (void) 
{
	initPL9823();
	TSI_Init();
	
	int i;
	int j;
	int xcounter = 0;
	int xpos = 1;
	int xb = 1;
	int ycounter = 0;
	int ypos = 1;
	int yb = 1;
	int zcounter = 0;
	int zpos = 1;
	int zb = 1;
	
	while(1)
	{
		if (TSI_ReadSlider() == 0)
		{
			xcounter++;
			if(xcounter==11)
			{
				xcounter=0;
				if(xb)xpos++;
				else xpos--;
				if(xpos == 1) xb = 1;
				if(xpos == Xsize) xb = 0;
			}
			
			ycounter++;
			if(ycounter==13)
			{
				ycounter=0;
				if(yb)ypos++;
				else ypos--;
				if(ypos == 1) yb = 1;
				if(ypos == Ysize) yb = 0;
			}
			
			zcounter++;
			if(zcounter==17)
			{
				zcounter=0;
				if(zb)zpos++;
				else zpos--;
				if(zpos == 1) zb = 1;
				if(zpos == Zsize) zb = 0;
			}
			
			clearAll();
			for(i=1;i<=Ysize;i++)
			{
				for(j =1; j<=Zsize;j++)
					setColor(xpos,i,j,0x0e0000);
			}
			
			for(i=1;i<=Xsize;i++)
			{
				for(j =1; j<=Zsize;j++)
					setColor(i,ypos,j,0x000e00);
			}
			
			for(i=1;i<=Xsize;i++)
			{
				for(j =1; j<=Ysize;j++)
					setColor(i,j,zpos,0x00000e);
			}
			updateLeds();
		}
		delay(400000);
	}
	
}
