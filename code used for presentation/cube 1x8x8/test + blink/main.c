#include "PL9823.h"
#include "tsi.h"
#include "opttest.h"
#include "blink.h"

int numberOfStates = 2;
int state = 0;
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
	int del = 1000000;
	
	
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
					state--;
					state = (state+numberOfStates) % numberOfStates;
				}
				
				if(slider > 50)
				{
					state++;
					state = (state+numberOfStates) % numberOfStates;
				}
			}
			pressed = 1;
		}
		else pressed = 0;
		
		// if state change prepare current state if needed
		if(lastState != state)
		{
			switch(state)
			{
				case 0: // prepare opticalTest
					prepareOptTest();
					break;
				
				case 1: // prepare blink
					prepareBlink();
					break;
				
				default:
					break;
			}
		}
		
		// update lastState
		lastState = state;
		
		// display on LEDs current state (only one frame!!! or "do one step" function) 
		switch(state)
		{
			case 0: // show opticalTest
				stepOptTest();
				break;
			
			case 1: // show blink
				stepBlink();
				break;
			
			default:
				break;
		}
		
		delay(del);
	}
	
	//opticalTest();
	
	
}
