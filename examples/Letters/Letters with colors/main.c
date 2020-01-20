#include "PL9823.h"

int textColorsTable[9];

int main (void) 
{
	initPL9823();
	initLetters();
	makeTape("I < ele  ");
	int i= tapeLength - 2;
	textColorsTable[0] = 0x0000ff;
	textColorsTable[2] = 0xff0000; 
	textColorsTable[4] = 0x00ff00; 
	textColorsTable[5] = 0x00ffff; 
	textColorsTable[6] = 0xff00ff; 

	while(1)
	{
		clearAll();
    showTapeColored(1,i,textColorsTable);
		updateLeds();
		i++;
		i%=tapeLength;
		delay(2000000);
	}
}