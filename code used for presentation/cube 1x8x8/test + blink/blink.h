#ifndef blink_h
#define blink_h

#include "PL9823.h"
#include <stdlib.h>

static struct RGB
{
	int r;
	int g;
	int b;
} LED;

static int scalerB = 16;
static int blinksPerFrameB = 10;

static struct RGB blinkColorTable[Ysize][Zsize];

void blinkOnce(void);
void dim(void);
void prepareBlink(void);
void stepBlink(void);

#endif /* blink_h */
