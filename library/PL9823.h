#ifndef rgbledlib_h
#define rgbledlib_h

#include "MKL46Z4.h" 

// control variables 

#define Xsize 1 // number of walls
#define Ysize 8 // height of a single wall
#define Zsize 8 // single wall length
#define numLetters 64 // number of all letters
#define tapeLength 10 // length of letters tape (how many letters)

// end control variables 

// data

static uint32_t data[Ysize * Zsize * 24]; // data for display on LEDs
static uint8_t letters[numLetters][5];
static int tmpTapeLength = 0;
static int table[8][tapeLength*6-1];

// end data

// aviable function
void initPL9823(void);
void updateLeds(void);

void setColor(int x, int y, int z, int color);
void setRGB(int x, int y, int z, uint8_t r, uint8_t g, uint8_t b);
void setWhite(int x, int y, int z);
void clear(int x, int y, int z);
void clearAll(void);

void initLetters(void);
int chartoletter(char x);
void makeTape(const uint8_t *a);
void showTape(int n, int color);

void delay(int count);

void opticalTest(void);

// end aviable function


#endif /* rgbledlib_h*/
