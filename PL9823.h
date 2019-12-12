#ifndef rgbledlib_h
#define rgbledlib_h

#include "MKL46Z4.h" 

#define numLED 1

// unia na dane

uint32_t data[1536]; // 64 * 24 

// alfabet template

void updateLeds(void);
void setColor(int x, int y, int z, uint8_t r, uint8_t g, uint8_t b);
void demo(void);


#endif
