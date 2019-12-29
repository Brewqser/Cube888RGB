#include "PL9823.h"

int main (void) 
{
	initPL9823();
	
	int i=0;
	initLetters();
	makeTape("I love ELE   ");
	
	while(1)
	{
    showTape(1,i,0x0000ff);
		updateLeds();
		i++;
		i%=14;
		delay(100000);
	}
}

