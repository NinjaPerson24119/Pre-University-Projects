#include "MathGeneralFunctions.h"
#include <cmath>

namespace ctm
{

//Checks if a number is within a range (Not including the specified boundaries)
bool inrange(float num, float boundary1, float boundary2)
{
	//Calculate highest and lowest boundary
	float lowest, highest;
	if(boundary1 < boundary2)
	{
		lowest = boundary1;
		highest = boundary2;
	}
	else
	{
		lowest = boundary2;
		highest = boundary1;
	}

	//Check if number is within range
	if(num < highest && num >lowest)
		return true;
	else
		return false;
}

//Gets the distance between two 2D points (Unflagging dosqrt will make the function return the squared distance)
float distance(float x1, float y1, float x2, float y2, bool dosqrt)
{
	float val = (float)(pow(2,(x2 - x1))+pow(2,(y2 - y1)));
	if(dosqrt == true)
		val = (float)sqrt(val);
	return val;
}

//Gets the distance between two 3D points (Unflagging dosqrt will make the function return the squared distance)
float distance(float x1, float y1, float z1, float x2, float y2, float z2, bool dosqrt)
{
	float val = (float)(pow(2, (x2 - x1)) + pow(2, (y2 - y1)) + pow(2, (z2 - z1)));
	if(dosqrt == true)
		val = (float)sqrt(val);
	return val;
}

//Finds the lowest power of an exponent that is atleast greater than a specified number
unsigned int lowestpowgreaterthan(unsigned int min, unsigned int exponent)
{
	unsigned int current = 0; //Current power
	for(unsigned int count = 0; current < min; ++count)
	{
		current = (unsigned int)pow(exponent,count);
	}
	return current;
}

}