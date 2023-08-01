#include "cPoint.h"

//Constructor
point::point(FLOAT32 iX, FLOAT32 iY):
x(iX),
y(iY){}

//Operator =
point& point::operator=(point RHS)
{
	set_point(RHS.x,RHS.y);
	return *this;
}

//Operator ==
bool point::operator==(point RHS)
{
	if((x == RHS.x) && (y == RHS.y))
		return true;
	else
		return false;
}

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