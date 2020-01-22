#include "pixelart.h"

void preparePixelart(void)
{
	countPA = 0;
	framesPA = 4;
}

void stepPixelart(void)
{
	switch(countPA)
	{
		case 0:
			clearAll();
			makePixelArt(1, pixelart, 8, 8);
			updateLeds();
			break;
		
		case 1:
			clearAll();
			makePixelArt(1, pixelartRight, 8, 8);
			updateLeds();
			break;
		
		case 2:
			clearAll();
			makePixelArt(1, pixelart, 8, 8);
			updateLeds();
			break;
		
		case 3:
			clearAll();
			makePixelArt(1, pixelartLeft, 8, 8);
			updateLeds();
			break;
	}
	delay(600000);
	
	countPA++;
	countPA%=framesPA;
}