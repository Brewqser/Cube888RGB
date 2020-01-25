#include "PL9823.h"

int main (void) 
{
	initPL9823();
		
	int tmp = 0x0f0000;
	int i=1;
	int j=1;
	int k=1;
	int count = 0;
	clearAll();

	while (1)
	{
		clearAll();
		setColor(2,2,2,tmp);
		setColor(2,3,2,tmp);
		setColor(3,3,2,tmp);
		setColor(3,2,2,tmp);
		setColor(2,2,3,tmp);
		setColor(2,3,3,tmp);
		setColor(3,3,3,tmp);
		setColor(3,2,3,tmp);
		
		updateLeds();
		delay(5000000);
		
		clearAll();
		
		for(i = Xsize; i >= 1; i--)
		{
			for(j = 1; j <= Ysize; j++)
			{
				setColor(i,j,1,tmp);
				setColor(i,j,4,tmp);
			}
		}
		
		for(i = Xsize; i >= 1; i--)
		{
			for(j = 1; j <= Zsize; j++)
			{
				setColor(i,1,j,tmp);
				setColor(i,4,j,tmp);
			}
		}
		
		for(i = Zsize; i >= 1; i--)
		{
			for(j = 1; j <= Ysize; j++)
			{
				setColor(1,i,j,tmp);
				setColor(4,i,j,tmp);
			}
		}
		
		updateLeds();
		delay(5000000);
		/*
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
		*/
	}
}
