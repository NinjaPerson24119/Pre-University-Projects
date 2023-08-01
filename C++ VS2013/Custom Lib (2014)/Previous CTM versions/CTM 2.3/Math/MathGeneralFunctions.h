#ifndef CTM_MATHGENERALFUNCTIONS_H
#define CTM_MATHGENERALFUNCTIONS_H

namespace ctm
{

//Comparaison functions
bool inrange(float num, float boundary1, float boundary2); //Checks if a number is within a range (Not including the specified boundaries)

//Distance functions
float distance(float x1, float y1, float x2, float y2, bool dosqrt = true); //Gets the distance between two 2D points (Unflagging dosqrt will make the function return the squared distance)
float distance(float x1, float y1, float z1, float x2, float y2, float z2, bool dosqrt = true); //Gets the distance between two 3D points (Unflagging dosqrt will make the function return the squared distance)

//Exponent functions
unsigned int lowestpowgreaterthan(unsigned int min, unsigned int exponent); //Finds the lowest power of an exponent that is atleast greater than a specified number

}

#endif