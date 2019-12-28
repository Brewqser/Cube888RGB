#ifndef rgbledlib_h
#define rgbledlib_h

#include "MKL46Z4.h" 

#define numLED 1

// controls variables 

#define Xsize 1 // number of walls
#define Ysize 8 // height of a single wall
#define Zsize 8 // single wall length

// end controls variables 

// data
static uint32_t data[Ysize * Zsize * 24]; // data for display on LEDs

// end data

// aviable function
void initPL9823(void);
void updateLeds(void);
void setColor(int x, int y, int z, int color);
void setRGB(int x, int y, int z, uint8_t r, uint8_t g, uint8_t b);
void setWhite(int x, int y, int z);
void clear(int x, int y, int z);
void clearAll();

void delay(int count);

void opticalTest(void);

// end aviable function



#endif /* rgbledlib_h*/
