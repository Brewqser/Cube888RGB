#ifndef tiles_h
#define tiles_h

#include "PL9823.h"
#include <stdlib.h>

static struct Tail
{
	int x;
	int y;
	int color;
} tail;

static struct Tail tailTable[8];
static struct Tail aviable[4];
static int avT = 0;

static int oT[5][5];

void updateT(void);
void getAviableT(int n);
void move(int n, int del);
void prepareTiles(void);
void stepTiles(int del);

#endif /* tiles_h*/
