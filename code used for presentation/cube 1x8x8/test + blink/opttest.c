#include "opttest.h"

void prepareOptTest(void)
{
	tmpOT = (1 << 24);
}

void stepOptTest(void)
{
	int i;
	int j;
	int k;
	clearAll();
	for(i = 1; i <= Xsize; i++)
	{
		for(j = 1; j <= Ysize; j++)
		{
			for(k = 1; k <= Zsize; k++)
				setColor(i,j,k,tmpOT);
		}
	}
	updateLeds();
	tmpOT/=2;
	tmpOT = (tmpOT == 1 ? (1 << 24) : tmpOT);
}
