#ifndef buttons_h
#define buttons_h

#include "MKL46Z4.h" 

#define button1 0			
#define button3 1

const static uint32_t button_mask[] = {1UL << 3, 1UL << 12};

void buttonsInitialize(void);
int32_t button1Read(void);
int32_t button3Read(void);

#endif
