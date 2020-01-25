#include "PL9823.h"

int main (void) 
{
	initPL9823();
		
	int tmp1 = 0x0f0000;
	int tmp2 = 0x000f00;
	int tmp3 = 0x00000f;
	int i=1;
	int j=1;
	int k=1;
	int count = 0;
	clearAll();

	while (1)
	{
		for(i = Xsize; i >= 1; i--)
		{
			for(j = 1; j <= Ysize / 2; j++)
			{
				for(k = 1; k <= Zsize; k++)
				{
					if(count == 0) setColor(i,j * 2 - 1,k,tmp1);
					if(count == 1) setColor(i,j * 2 - 1,k,tmp2);
					if(count == 2) setColor(i,j * 2 - 1,k,tmp3);
					updateLeds();
					
					delay(1000000);
				}
				
				for(k = Zsize; k >= 1; k--)
				{
					if(count == 0) setColor(i,j * 2 ,k,tmp1);
					if(count == 1) setColor(i,j * 2 ,k,tmp2);
					if(count == 2) setColor(i,j * 2 ,k,tmp3);
					updateLeds();
					
					delay(1000000);
				}
			}
		}
		count = (count + 1) % 3;
		clearAll();
	}
}
