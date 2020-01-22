#include "PL9823.h"

int main (void) 
{
	initPL9823();
	
	int del = 1000000;
	int tmp = 0x202000;
	int i=1;
	int j=1;
	int k=1;
	clearAll();

	while (1)
	{
		for(i = 1; i <= Xsize; i++)
		{
			for(j = 1; j <= Ysize / 2; j++)
			{
				for(k = 1; k <= Zsize; k++)
				{
					setColor(i,j * 2 - 1,k,tmp);
					updateLeds();
					
					delay(del);
				}
				
				for(k = Zsize; k >= 1; k--)
				{
					setColor(i,j * 2 ,k,tmp);
					updateLeds();
					
					delay(del);
				}
			}
		}
		clearAll();
	}
}

