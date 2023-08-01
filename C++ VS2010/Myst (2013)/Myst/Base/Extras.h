#ifndef EXTRAS_H
#define EXTRAS_H

#ifndef MATH
#define MATH
#include <math.h>
#endif

//Checks if a number is even or odd
enum EVEN_ODD { EVEN, ODD };
EVEN_ODD even_odd(int number)
{
	if(number/2 * 2 == number)
		return EVEN;
	else
		return ODD;
}

//Checks if a number is within a range (INT)
bool range(int num, int lowest, int highest)
{
	if(num >= lowest && num <= highest) 
		return true;
	else 
		return false;
}

//Checks if a number is within a range (FLOAT)
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
	return sqrt(pow(x2-x1,2))+(pow(y2-y1,2));
}

//Makes a positive number negative and vice versa
float flipsign(float num)
{
	if(num > 0) 
		num = num + num*2;
	else
		num = num - num*2;
	return num;
}

#endif