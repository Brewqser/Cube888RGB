#include "PL9823.h"

void initPL9823(void)
{
	// portB0 
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB->PCR[0] = PORT_PCR_MUX(1);
	PTB->PDDR |= (1UL );
}

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

void updateLeds(void)
{
	int j=-1;
	
	// desable interrupts 
	while ( j < (numLED*24) -1)
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
	// anable interrupts
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

void demo(void)
{
	
}


void delay(int count)
{
	uint32_t x;
	
	for(x=0; x < count; x++){}
}

