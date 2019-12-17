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

void setColor(int x, int y, int z, int color)
{
	/*--------------------------------------------------------------------------
	seting color on diode with position x y z ( for now x = 1 )
	--------------------------------------------------------------------------*/
	unsigned int tmp = 0;
	int i = 0;
	
	for (tmp = 0; tmp <= 23; tmp++)
	{
		if (y % 2 == 1)
		{
			i = 24 * ((y-1)*(Zsize) + (z-1)) + tmp;
			data[i] = (color & (1 << (23 - tmp)) ? 1 : 0);
		}
		else
		{
			i = 24 * (y * Zsize - z) + tmp;  
			data[i] = (color & (1 << (23 - tmp)) ? 1 : 0);
		}
	}
}

void setRGB(int x, int y, int z, uint8_t r, uint8_t g, uint8_t b)
{
	/*--------------------------------------------------------------------------
	seting color with specified r g b on diode with position x y z 
	--------------------------------------------------------------------------*/
	int kol = (r << 16) + (g << 8) + b;

	setColor(x,y,z,kol);
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

void opticalTest(void)
{
	/*--------------------------------------------------------------------------
	testing each bit in conected diodes with some delay
	--------------------------------------------------------------------------*/
	int tmp = (1 << 24);
	int i=1;
	int j=1;

	while (1)
	{
		tmp/=2;
		for(i = 1; i <= Ysize; i++)
		{
			for(j = 1; j <= Zsize; j++)
			{
				setColor(1,i,j,tmp);
			}
		}
		updateLeds();
		tmp = (tmp == 1 ? (1 << 24) : tmp);
		delay(10000000);
	}
}

// end done 

