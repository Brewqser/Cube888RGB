#include "PL9823.h"

int main (void) 
{
	initPL9823();
	int del = 10000000;
	
	while(1)
	{
		setColor(1,1,1,0x230015);
		setRGB(1,1,2,0,31,31);
		setWhite(1,1,3);
		updateLeds();
		delay(del);
		
		clear(1,1,2);
		updateLeds();
		delay(del);
		
		clearAll();
		updateLeds();
		delay(del);
	}
}

