#ifndef POINT_H
#define POINT_H

//////////////////////////////////////
//Point class
class point
{
public:
	point(float iX, float iY);
	void set_point(float nX, float nY) { x = nX; y = nY; }
	point& operator=(point RHS);
	bool operator==(point RHS);
	point& operator+(point RHS);
	point& operator-(point RHS);
	float x,y;
};

//Constructor
point::point(float iX = 0, float iY = 0):
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
//////////////////////////////////////

#endif