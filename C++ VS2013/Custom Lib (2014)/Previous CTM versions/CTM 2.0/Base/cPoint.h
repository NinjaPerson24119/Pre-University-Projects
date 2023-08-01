#ifndef POINT_H
#define POINT_H

#include "Base.h"

//////////////////////////////////////
//Point class
class point
{
public:
	point(FLOAT32 iX = 0, FLOAT32 iY = 0);
	void set_point(FLOAT32 nX, FLOAT32 nY) { x = nX; y = nY; }
	point& operator=(point RHS);
	BOOL8 operator==(point RHS);
	point& operator+(point RHS);
	point& operator-(point RHS);
	FLOAT32 x,y;
};
//////////////////////////////////////

#endif