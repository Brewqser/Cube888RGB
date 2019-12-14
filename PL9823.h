#ifndef rgbledlib_h
#define rgbledlib_h

#include "MKL46Z4.h" 

#define numLED 1

// globals for cube
#define maxX = 1;
#define maxY = 1;
#define maxZ = 1;

// dane
static uint32_t data[1536]; // 64 * 24 ( ile diod * 24 )  

// alfabet template

// aviable function
void initPL9823(void);
void opticalTest(void);
void updateLeds(void);
void setRGB(int x, int y, int z, uint8_t r, uint8_t g, uint8_t b);
void setColor(int x, int y, int z, int color);
void delay(int count);


void demo(void);

#endif /* rgbledlib_h*/
