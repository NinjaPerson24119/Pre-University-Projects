#include "Extras.h"
#include <math.h>

//Checks if a number is within a range
BOOL8 range(FLOAT32 num, FLOAT32 lowest, FLOAT32 highest)
{
	if(num >= lowest && num <= highest) 
		return true;
	else 
		return false;
}

//Returns distance between two points
FLOAT32 distance(FLOAT32 x1, FLOAT32 y1, FLOAT32 x2, FLOAT32 y2)
{
	FLOAT32 disx = x2 - x1; disx = disx * disx;
	FLOAT32 disy = y2 - y1; disy = disy * disy;
	return sqrt(disx + disy);
}

//Finds the lowest power of two a number can fit in
UINT32 lowestpow2(UINT32 min)
{
	UINT32 pow = 2;
	while(pow < min)
	{
		pow = pow*2;
	}
	return pow;
}