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

//Makes a positive number negative and vice versa
float flipsign(float num)
{
	if(num > 0) 
		num = num + num*2;
	else
		num = num - num*2;
	return num;
}

//Rotates a point
point rotatepoint(point coord, point axis, angle degrees)
{
	float c = cosf(degrees.get_radians()); //Calculate cosine and sine
	float s = sinf(degrees.get_radians());
	coord = coord - axis; //Translate to origin
	float adjustx = (coord.x*c) - (coord.y*s); //Calculate new x
	float adjusty = (coord.x*s) + (coord.y*c);
	coord = point(adjustx,adjusty) + axis; //Translate away from origin
	return coord;
}
#endif