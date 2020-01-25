#ifndef rgbledlib_h
#define rgbledlib_h

#include "MKL46Z4.h" 

// control variables 

#define Xsize 4 // number of walls
#define Ysize 4 // height of a single wall
#define Zsize 4 // single wall length
#define numLetters 65 // number of all letters

static int pinTable[Xsize] = {0,1,2,3}; // table that conteins pin numbers for walls 

// end control variables 

// data

static uint32_t data[Ysize * Zsize * 24]; // data for display on LEDs
static uint8_t letters[numLetters][5];
static int tapeLength = 0;
static int table[8][200];

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
void showTape(int x, int n, int color);
void showTapeColored(int x, int n,const int *colors);

void makePixelArt(int x, const int* table, int ys, int zs);

void delay(int count);

void opticalTest(void);

// end aviable function


#endif /* rgbledlib_h*/
