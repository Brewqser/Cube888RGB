#include "txt.h"

void prepareTxt(void)
{
	initLetters();
	makeTape("Prosimy o zwolnienie  ");
	counterT = tapeLength - 2;
	textColorsTable[0] = 0x00000f;
	textColorsTable[1] = 0x00000f;
	textColorsTable[2] = 0x00000f;
	textColorsTable[3] = 0x00000f;
	textColorsTable[4] = 0x00000f;
	textColorsTable[5] = 0x00000f;
	textColorsTable[6] = 0x00000f;
	
	textColorsTable[8] = 0x0f0000;
	
	textColorsTable[10] = 0x000f00;
	textColorsTable[11] = 0x000f00;
	textColorsTable[12] = 0x000f00;
	textColorsTable[13] = 0x000f00;
	textColorsTable[14] = 0x000f00;
	textColorsTable[15] = 0x000f00;
	textColorsTable[16] = 0x000f00;
	textColorsTable[17] = 0x000f00;
	textColorsTable[18] = 0x000f00;
	textColorsTable[19] = 0x000f00;
}

void stepTxt()
{
		clearAll();
    showTapeColored(1,counterT,textColorsTable);
		updateLeds();
		counterT++;
		counterT%=tapeLength;
}
