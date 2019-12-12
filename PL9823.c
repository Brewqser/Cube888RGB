#include "PL9823.h"

void updateLeds()
{
	int j=-1;
	while ( j < (numLED*24) -1)
	{
		PTB->PDOR = 255;
		PTB->PDOR = 255;
		PTB->PDOR = data[j+1];
		j++;
		PTB->PDOR = data[j];
		PTB->PDOR = 0;
		PTB->PDOR = 0;
	}
}

void setColor(int x, int y, int z, uint8_t r, uint8_t g, uint8_t b)
{
	//int tmp = 0;
	//int kol = (r << 16) + (g << 8) + b;
	
	/*
	
	for ( tmp = 0; tmp <= 23 ;tmp++ )
	{
		if (kol & (1 << (23 - tmp)))
			data[*24 + tmp] = 1;
		else 
			data[numLED*24 + tmp] = 0;
	}
	
	*/
}

void demo()
{
	
}

