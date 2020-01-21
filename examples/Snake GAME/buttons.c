#include "buttons.h"

void buttonsInitialize(void){

	SIM->SCGC5 |=  SIM_SCGC5_PORTC_MASK; 		
	PORTC->PCR[3] |= PORT_PCR_MUX(1);      
	PORTC->PCR[12] |= PORT_PCR_MUX(1);      
	
	PTC->PDDR &= ~button_mask[button1]; 
	PTC->PDDR &= ~button_mask[button3]; 
	
	PORTC->PCR[3] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; 
	PORTC->PCR[12] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
}

int32_t button1Read(){
	return PTC->PDIR & button_mask[button1];						
}

int32_t button3Read(){
	return PTC->PDIR & button_mask[button3];
}
