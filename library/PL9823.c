#include "PL9823.h"

// done

void initPL9823(void)
{
	int i=0;
	// portB0 
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	for(i=0;i<Xsize;i++)
	{
		PORTB->PCR[pinTable[i]] = PORT_PCR_MUX(1);
		PTB->PDDR |= (1UL << pinTable[i]);
	}
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

	__enable_irq();	// enable interrupts
}

void setColor(int x, int y, int z, int color)
{
	/*--------------------------------------------------------------------------
	seting color on diode with position x y z
	--------------------------------------------------------------------------*/
	unsigned int tmp = 0;
	int i = 0;
	
	for (tmp = 0; tmp <= 23; tmp++)
	{
		if (y % 2 == 1)
		{
			i = 24 * ((y-1)*(Zsize) + (z-1)) + tmp;
		}
		else
		{
			i = 24 * (y * Zsize - z) + tmp;
		}
		data[i] = ( (color & (1 << (23 - tmp)) ? 1 : 0) ) << pinTable[x-1];
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

void setWhite(int x, int y, int z)
{
	/*--------------------------------------------------------------------------
	seting White on diode with position x y z 
	--------------------------------------------------------------------------*/
	int kol = (255 << 16) + (255 << 8) + 255;
	
	setColor(x,y,z,kol);
}

void clear(int x, int y, int z)
{
	/*--------------------------------------------------------------------------
	seting 0 (clear) on diode with position x y z 
	--------------------------------------------------------------------------*/
	int kol = 0;
	
	setColor(x,y,z,kol);
}

void clearAll(void)
{
	/*--------------------------------------------------------------------------
	seting 0 (clear) on diode all LEDs 
	--------------------------------------------------------------------------*/
	int i = 0;
	
	for (i = 0; i < Ysize * Zsize * 24; i++)
	{
		data[i] = 0;
	}
}

void initLetters(void)
{
	/*--------------------------------------------------------------------------
	hard coded letters
	--------------------------------------------------------------------------*/
	// 0
	letters[0][0] = 62;
	letters[0][1] = 69;
	letters[0][2] = 73;
	letters[0][3] = 81;
	letters[0][4] = 62;

	// 1
	letters[1][0] = 17;
	letters[1][1] = 33;
	letters[1][2] = 127;
	letters[1][3] = 1;
	letters[1][4] = 1;

	// 2
	letters[2][0] = 33;
	letters[2][1] = 67;
	letters[2][2] = 69;
	letters[2][3] = 73;
	letters[2][4] = 49;

	// 3
	letters[3][0] = 34;
	letters[3][1] = 65;
	letters[3][2] = 73;
	letters[3][3] = 73;
	letters[3][4] = 54;

	// 4
	letters[4][0] = 4;
	letters[4][1] = 12;
	letters[4][2] = 20;
	letters[4][3] = 36;
	letters[4][4] = 127;

	// 5
	letters[5][0] = 121;
	letters[5][1] = 73;
	letters[5][2] = 73;
	letters[5][3] = 73;
	letters[5][4] = 70;

	// 6
	letters[6][0] = 62;
	letters[6][1] = 73;
	letters[6][2] = 73;
	letters[6][3] = 73;
	letters[6][4] = 38;

	// 7
	letters[7][0] = 64;
	letters[7][1] = 64;
	letters[7][2] = 71;
	letters[7][3] = 72;
	letters[7][4] = 112;

	// 8
	letters[8][0] = 54;
	letters[8][1] = 73;
	letters[8][2] = 73;
	letters[8][3] = 73;
	letters[8][4] = 54;

	// 9
	letters[9][0] = 50;
	letters[9][1] = 73;
	letters[9][2] = 73;
	letters[9][3] = 73;
	letters[9][4] = 62;

	// A
	letters[10][0] = 63;
	letters[10][1] = 72;
	letters[10][2] = 72;
	letters[10][3] = 72;
	letters[10][4] = 63;

	// B
	letters[11][0] = 127;
	letters[11][1] = 73;
	letters[11][2] = 73;
	letters[11][3] = 73;
	letters[11][4] = 54;

	// C
	letters[12][0] = 62;
	letters[12][1] = 65;
	letters[12][2] = 65;
	letters[12][3] = 65;
	letters[12][4] = 34;

	// D
	letters[13][0] = 127;
	letters[13][1] = 65;
	letters[13][2] = 65;
	letters[13][3] = 65;
	letters[13][4] = 62;

	// E
	letters[14][0] = 127;
	letters[14][1] = 73;
	letters[14][2] = 73;
	letters[14][3] = 73;
	letters[14][4] = 65;

	// F
	letters[15][0] = 127;
	letters[15][1] = 72;
	letters[15][2] = 72;
	letters[15][3] = 72;
	letters[15][4] = 64;

	// G
	letters[16][0] = 62;
	letters[16][1] = 65;
	letters[16][2] = 73;
	letters[16][3] = 73;
	letters[16][4] = 46;

	// H
	letters[17][0] = 127;
	letters[17][1] = 8;
	letters[17][2] = 8;
	letters[17][3] = 8;
	letters[17][4] = 127;

	// I
	letters[18][0] = 65;
	letters[18][1] = 65;
	letters[18][2] = 127;
	letters[18][3] = 65;
	letters[18][4] = 65;

	// J
	letters[19][0] = 2;
	letters[19][1] = 1;
	letters[19][2] = 1;
	letters[19][3] = 1;
	letters[19][4] = 126;

	// K
	letters[20][0] = 127;
	letters[20][1] = 8;
	letters[20][2] = 20;
	letters[20][3] = 34;
	letters[20][4] = 65;

	// L
	letters[21][0] = 127;
	letters[21][1] = 1;
	letters[21][2] = 1;
	letters[21][3] = 1;
	letters[21][4] = 1;

	// M
	letters[22][0] = 127;
	letters[22][1] = 32;
	letters[22][2] = 16;
	letters[22][3] = 32;
	letters[22][4] = 127;

	// N
	letters[23][0] = 127;
	letters[23][1] = 16;
	letters[23][2] = 8;
	letters[23][3] = 4;
	letters[23][4] = 127;

	// O
	letters[24][0] = 62;
	letters[24][1] = 65;
	letters[24][2] = 65;
	letters[24][3] = 65;
	letters[24][4] = 62;

	// P
	letters[25][0] = 127;
	letters[25][1] = 72;
	letters[25][2] = 72;
	letters[25][3] = 72;
	letters[25][4] = 48;

	// Q
	letters[26][0] = 62;
	letters[26][1] = 65;
	letters[26][2] = 69;
	letters[26][3] = 67;
	letters[26][4] = 63;

	// R
	letters[27][0] = 127;
	letters[27][1] = 72;
	letters[27][2] = 76;
	letters[27][3] = 74;
	letters[27][4] = 49;

	// S
	letters[28][0] = 50;
	letters[28][1] = 73;
	letters[28][2] = 73;
	letters[28][3] = 73;
	letters[28][4] = 38;

	// T
	letters[29][0] = 64;
	letters[29][1] = 64;
	letters[29][2] = 127;
	letters[29][3] = 64;
	letters[29][4] = 64;

	// U
	letters[30][0] = 126;
	letters[30][1] = 1;
	letters[30][2] = 1;
	letters[30][3] = 1;
	letters[30][4] = 126;

	// V
	letters[31][0] = 124;
	letters[31][1] = 2;
	letters[31][2] = 1;
	letters[31][3] = 2;
	letters[31][4] = 124;

	// W
	letters[32][0] = 127;
	letters[32][1] = 2;
	letters[32][2] = 4;
	letters[32][3] = 2;
	letters[32][4] = 127;

	// X
	letters[33][0] = 99;
	letters[33][1] = 20;
	letters[33][2] = 8;
	letters[33][3] = 20;
	letters[33][4] = 99;

	// Y
	letters[34][0] = 112;
	letters[34][1] = 8;
	letters[34][2] = 7;
	letters[34][3] = 8;
	letters[34][4] = 112;

	// Z
	letters[35][0] = 67;
	letters[35][1] = 69;
	letters[35][2] = 73;
	letters[35][3] = 81;
	letters[35][4] = 97;

	// a
	letters[36][0] = 14;
	letters[36][1] = 17;
	letters[36][2] = 17;
	letters[36][3] = 31;
	letters[36][4] = 1;

	// b
	letters[37][0] = 127;
	letters[37][1] = 17;
	letters[37][2] = 17;
	letters[37][3] = 17;
	letters[37][4] = 14;

	// c
	letters[38][0] = 14;
	letters[38][1] = 17;
	letters[38][2] = 17;
	letters[38][3] = 17;
	letters[38][4] = 10;

	// d
	letters[39][0] = 14;
	letters[39][1] = 17;
	letters[39][2] = 17;
	letters[39][3] = 17;
	letters[39][4] = 127;

	// e
	letters[40][0] = 14;
	letters[40][1] = 21;
	letters[40][2] = 21;
	letters[40][3] = 21;
	letters[40][4] = 8;

	// f
	letters[41][0] = 8;
	letters[41][1] = 8;
	letters[41][2] = 63;
	letters[41][3] = 72;
	letters[41][4] = 40;

	// g
	letters[42][0] = 24;
	letters[42][1] = 37;
	letters[42][2] = 37;
	letters[42][3] = 37;
	letters[42][4] = 30;

	// h
	letters[43][0] = 127;
	letters[43][1] = 16;
	letters[43][2] = 16;
	letters[43][3] = 16;
	letters[43][4] = 15;

	// i
	letters[44][0] = 0;
	letters[44][1] = 0;
	letters[44][2] = 95;
	letters[44][3] = 0;
	letters[44][4] = 0;

	// j
	letters[45][0] = 2;
	letters[45][1] = 1;
	letters[45][2] = 1;
	letters[45][3] = 1;
	letters[45][4] = 94;

	// k
	letters[46][0] = 127;
	letters[46][1] = 4;
	letters[46][2] = 4;
	letters[46][3] = 10;
	letters[46][4] = 17;

	// l
	letters[47][0] = 0;
	letters[47][1] = 0;
	letters[47][2] = 127;
	letters[47][3] = 0;
	letters[47][4] = 0;

	// m
	letters[48][0] = 31;
	letters[48][1] = 16;
	letters[48][2] = 12;
	letters[48][3] = 16;
	letters[48][4] = 31;

	// n
	letters[49][0] = 31;
	letters[49][1] = 8;
	letters[49][2] = 16;
	letters[49][3] = 16;
	letters[49][4] = 31;

	// o
	letters[50][0] = 14;
	letters[50][1] = 17;
	letters[50][2] = 17;
	letters[50][3] = 17;
	letters[50][4] = 14;

	// p
	letters[51][0] = 31;
	letters[51][1] = 36;
	letters[51][2] = 36;
	letters[51][3] = 36;
	letters[51][4] = 24;

	// q
	letters[52][0] = 24;
	letters[52][1] = 36;
	letters[52][2] = 36;
	letters[52][3] = 36;
	letters[52][4] = 31;

	// r
	letters[53][0] = 16;
	letters[53][1] = 15;
	letters[53][2] = 16;
	letters[53][3] = 16;
	letters[53][4] = 16;

	// s
	letters[54][0] = 9;
	letters[54][1] = 21;
	letters[54][2] = 21;
	letters[54][3] = 21;
	letters[54][4] = 18;

	// t
	letters[55][0] = 0;
	letters[55][1] = 16;
	letters[55][2] = 127;
	letters[55][3] = 16;
	letters[55][4] = 0;

	// u
	letters[56][0] = 30;
	letters[56][1] = 1;
	letters[56][2] = 1;
	letters[56][3] = 1;
	letters[56][4] = 30;

	// v
	letters[57][0] = 28;
	letters[57][1] = 2;
	letters[57][2] = 1;
	letters[57][3] = 2;
	letters[57][4] = 28;

	// w
	letters[58][0] = 30;
	letters[58][1] = 1;
	letters[58][2] = 6;
	letters[58][3] = 1;
	letters[58][4] = 30;

	// x
	letters[59][0] = 17;
	letters[59][1] = 10;
	letters[59][2] = 4;
	letters[59][3] = 10;
	letters[59][4] = 17;

	// y
	letters[60][0] = 16;
	letters[60][1] = 8;
	letters[60][2] = 7;
	letters[60][3] = 8;
	letters[60][4] = 16;

	// z
	letters[61][0] = 17;
	letters[61][1] = 19;
	letters[61][2] = 21;
	letters[61][3] = 25;
	letters[61][4] = 17;

	// |||
	letters[62][0] = 255;
	letters[62][1] = 255;
	letters[62][2] = 255;
	letters[62][3] = 255;
	letters[62][4] = 255;

	// ' '
	letters[63][0] = 0;
	letters[63][1] = 0;
	letters[63][2] = 0;
	letters[63][3] = 0;
	letters[63][4] = 0;
	
	// <
	letters[64][0] = 24;
	letters[64][1] = 60;
	letters[64][2] = 30;
	letters[64][3] = 60;
	letters[64][4] = 24;
}

int chartoletter(char x)
{
	/*--------------------------------------------------------------------------
	decoding letter index based on ascii
	--------------------------------------------------------------------------*/
	int a = (int)x;

	if(a >= 48 && a <= 57) return a - 48;
	if(a >= 65 && a <= 90) return a - 55;
	if(a >= 97  && a <= 122) return a - 61;
	if(a == 32) return 63;
	if(a == 60) return 64; // if a == '<' show heart 
	return 62;
}

void makeTape(const uint8_t *a)
{
	/*--------------------------------------------------------------------------
	creating tape from text a and letters
	--------------------------------------------------------------------------*/
	int z = 0;
	int j = 0;
	int i = 0;
	int tmp = 0;
	tapeLength = 0;

	while ( *(a + tmp) != '\0')
	{
			for (j=7; j>=0; j--)
			{
					for (i=0; i<5; i++)
					{
							table[j][tapeLength + i] = ((letters[chartoletter(*(a + tmp))][i] & (1 << j)) >> j );
					}
			}
			z++;
			tmp++;
			tapeLength += 6;
	}
	tapeLength--;
	//tapeLength = tmpTapeLength;
}

void showTape(int x, int n, int color)
{
  /*--------------------------------------------------------------------------
	setting part of the table (from n yo n+7)	on data table
	--------------------------------------------------------------------------*/
	int j = 0;
	int i = 0;
	int k = 1;

	for (j = 8; j >= 1 ;j--)
	{
			k = 1;
			for(i = n; i < n+8; i++)
			{
				 if (table[j-1][i%tapeLength] == 1)
						setColor(x, j, k, color);
				 else 
						setColor(x, j, k, 0x000000);
				 
				 k=k+1;
			}
	}
	
}

void showTapeColored(int x, int n,const int *colors)
{
  /*--------------------------------------------------------------------------
	setting part of the table (from n yo n+7)	on data table 
	with specified colors
	
	colors come from colors table that mast be defined in main !!!
	--------------------------------------------------------------------------*/
	int j = 0;
	int i = 0;
	int k = 1;
	
	for (j = 8; j >= 1 ;j--)
	{
			k = 1;
			for(i = n; i < n+8; i++)
			{
				 if (table[j-1][i%tapeLength] == 1)
						setColor(x, j, k, *(colors + (i%tapeLength)/6));
				 else 
						setColor(x, j, k, 0x000000);
				 
				 k=k+1;
			}
	}
	
}

void makePixelArt(int x, const int* table, int ys, int zs)
{
	/*--------------------------------------------------------------------------
	updating data table with pixelart in table
	--------------------------------------------------------------------------*/
	int i=0;
	int j=0;

  for (i = 1; i <= ys; i++) 
      for (j = 1; j <= zs; j++) 
			{
				setColor(x,ys - i + 1,j, *(table+((i-1)*zs)+(j-1)));
			}
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
	int k=1;

	while (1)
	{
		tmp/=2;
		for(i = 1; i <= Xsize; i++)
		{
			for(j = 1; j <= Ysize; j++)
			{
				for(k = 1; k <= Zsize; k++)
					setColor(i,j,k,tmp);
			}
		}
		updateLeds();
		tmp = (tmp == 1 ? (1 << 24) : tmp);
		delay(1000000);
	}
}

// end done 

