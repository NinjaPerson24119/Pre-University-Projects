#include "cPoint.h"

namespace ctm
{

//Constructor
point::point(FLOAT32 iX, FLOAT32 iY):
x(iX),
y(iY){}

//Operator +
point& point::operator+(point RHS)
{
	x = x + RHS.x;
	y = y + RHS.y;
	return *this;
}

//Operator -
point& point::operator-(point RHS)
{
	x = x - RHS.x;
	y = y - RHS.y;
	return *this;
}

}