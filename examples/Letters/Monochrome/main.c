#include "PL9823.h"

int main (void) 
{
	initPL9823();
	
	int i=0;
	initLetters();
	makeTape("I < ELE   ");
	i=tapeLength - 2;

	while(1)
	{
		clearAll();
    		showTape(1,i,0x0000ff);
		updateLeds();
		i++;
		i%=tapeLength;
		delay(2000000);
	}
}