#include "txt.h"

void prepareTxt(void)
{
	initLetters();
	makeTape("Prosimy o zwolnienie  ");
	counterT = tapeLength - 2;
	textColorsTable[0] = 0x0000ff;
	textColorsTable[1] = 0x0000ff;
	textColorsTable[2] = 0x0000ff;
	textColorsTable[3] = 0x0000ff;
	textColorsTable[4] = 0x0000ff;
	textColorsTable[5] = 0x0000ff;
	textColorsTable[6] = 0x0000ff;
	
	textColorsTable[8] = 0xff0000;
	
	textColorsTable[10] = 0x00ff00;
	textColorsTable[11] = 0x00ff00;
	textColorsTable[12] = 0x00ff00;
	textColorsTable[13] = 0x00ff00;
	textColorsTable[14] = 0x00ff00;
	textColorsTable[15] = 0x00ff00;
	textColorsTable[16] = 0x00ff00;
	textColorsTable[17] = 0x00ff00;
	textColorsTable[18] = 0x00ff00;
	textColorsTable[19] = 0x00ff00;
}

void stepTxt()
{
		clearAll();
    showTapeColored(1,counterT,textColorsTable);
		updateLeds();
		counterT++;
		counterT%=tapeLength;
}
