#include "PL9823.h"

// done

void initPL9823(void)
{
	// portB0 
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB->PCR[0] = PORT_PCR_MUX(1);
	PTB->PDDR |= (1UL);
	
	/*--------------------------------------------------------------------------
	here you can add port E initialization
	port E have 8 GPIO pins on KL46Z board 
	so it is ez to set 8 walls for cube
	--------------------------------------------------------------------------*/	
}

void updateLeds(void)
{
	/*--------------------------------------------------------------------------
	"PWM" genarator wirte specyficly for FRDM KL56Z board
	it`s simple and works :P
	this while loop should generate PWM with 800 kHz freq (1.25 us) 
	when data[j] == 1 PWM duty cycle is 60% 
	and 
	when data[j] == 0 PWM duty cycle is 40% 
	
	!!! interapts should be disabled when you updating LEDs !!!
	--------------------------------------------------------------------------*/
	
	int j=-1; // tmp value for iteration
	
	__disable_irq();	// desable interrupts 

	while (j < (Ysize * Zsize * 24) - 1)
	{
		PTB->PDOR = 255;
		PTB->PDOR = 255;
		PTB->PDOR = data[j+1];
		j++;
		PTB->PDOR = data[j];
		PTB->PDOR = data[j];
		PTB->PDOR = data[j];
		PTB->PDOR = 0;
		PTB->PDOR = 0;
	}

	__enable_irq();	// anable interrupts
}

void delay(int count)
{
	/*--------------------------------------------------------------------------
	delay 
	yea simlpe for loop delay XD 
	--------------------------------------------------------------------------*/
	uint32_t x;
	for(x=0; x < count; x++){}
}

// end done 

void opticalTest(void)
{
	int tmp = ( 1 << 24);
	while (1)
	{
		tmp/=2;
		setColor(1,1,1,tmp);
		updateLeds();
		tmp = ( tmp == 0 ? (1 << 24) : tmp );
		delay(10000000);
	}
}



void setRGB(int x, int y, int z, uint8_t r, uint8_t g, uint8_t b)
{
	int tmp = 0;
	int kol = (r << 16) + (g << 8) + b;
	
	for ( tmp = 0; tmp <= 23 ;tmp++ )
	{
		if (kol & (1 << (23 - tmp)))
			data[(z-1)*24 + tmp] = (1 << 0);
		else 
			data[(z-1)*24 + tmp] = 0;
	}
}

void setColor(int x, int y, int z, int color)
{
	int tmp = 0;
	int kol = color;
	
	for ( tmp = 0; tmp <= 23 ;tmp++ )
	{
		if (kol & (1 << (23 - tmp)))
			data[(z-1)*24 + tmp] = (1 << 0);
		else 
			data[(z-1)*24 + tmp] = 0;
	}

}
