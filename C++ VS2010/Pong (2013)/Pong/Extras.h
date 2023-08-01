#ifndef EXTRAS_H
#define EXTRAS_H

#ifndef MATH
#define MATH
#include <math.h>
#endif

//Checks if a number is even
bool evennumber(int number)
{
	if(number/2 * 2 == number)
		return true;
	else
		return false;
}

//Checks if a number is within a range
bool range(float num, float lowest, float highest)
{
	if(num >= lowest && num <= highest) 
		return true;
	else 
		return false;
}

//Returns distance between two points
float distance(float x1, float y1, float x2, float y2)
{
	float disx = x2 - x1; disx = disx * disx;
	float disy = y2 - y1; disy = disy * disy;
	return sqrt(disx + disy);
}

//Distance function without square root
float distance2(float x1, float y1, float x2, float y2)
{
	float disx = x2 - x1; disx = disx * disx;
	float disy = y2 - y1; disy = disy * disy;
	return disx + disy;
}

#endif