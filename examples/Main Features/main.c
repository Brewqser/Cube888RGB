#include "PL9823.h"

int main (void) 
{
	initPL9823();
	
	while(1)
	{
		setColor(1,1,1,0x230015);
		setRGB(1,1,2,0,31,31);
		setWhite(1,1,3);
		updateLeds();
		delay(100000);
		
		clear(1,1,2);
		updateLeds();
		delay(100000);
		
		clearAll();
		updateLeds();
		delay(100000);
	}
}

