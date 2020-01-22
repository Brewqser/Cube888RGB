#include "PL9823.h"
#include "tsi.h"
#include "txt.h"

int numberOfStates = 10000001;
int state = 1000000;
int lastState = -1;

// init all
void initAll()
{
	initPL9823();
	TSI_Init();
}

int main (void) 
{
	initAll();
	
	int slider;
	int pressed = 0;
	prepareTxt();
	
	while(1)
	{
		slider = TSI_ReadSlider(); // read value from slider
		
		// TSI was pressed
		if(slider!=0 )
		{
			// pressed once 
			if(pressed == 0)
			{
				// devide slider by 2
				// and add or sub from current state to change it
				if(slider <= 50)
				{
					state+= 100000;
					state = (state+numberOfStates) % numberOfStates;
				}
				
				if(slider > 50)
				{
					state-= 100000;
					state = (state+numberOfStates) % numberOfStates;
				}
			}
			pressed = 1;
		}
		else pressed = 0;
		
		// update lastState
		lastState = state;
		
		// display on LEDs current state (only one frame!!! or "do one step" function) 
	  // show txt
		stepTxt();
		
		delay(state);
	}
}
