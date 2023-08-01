#ifndef CTM_POINT_H
#define CTM_POINT_H

#include "Base.h"

namespace ctm
{

//////////////////////////////////////
//Point class
class point
{
public:
	point(FLOAT32 iX = 0, FLOAT32 iY = 0);
	point& operator+(point RHS);
	point& operator-(point RHS);
	void set_point(FLOAT32 nX, FLOAT32 nY) { x = nX; y = nY; }
	FLOAT32 x,y;
};
//////////////////////////////////////

}

#endif