#include "Collisions.h"
#include <math.h>

namespace ctm
{

//One dimensional line hit
BOOL8 LineHit1D(FLOAT32 a1, FLOAT32 a2, FLOAT32 b1, FLOAT32 b2)
{
	if((a1 > b1) && (a1 < b2)) return true;
	if((a2 > b1) && (a2 < b2)) return true;
	return false;
}

//Block hit
BOOL8 BlockHit(FLOAT32 x1, FLOAT32 y1, FLOAT32 size1, FLOAT32 x2, FLOAT32 y2, FLOAT32 size2)
{
	BOOL8 x_inrange = false, y_inrange = false;
	if(range(x1,x2,x2+size2) == true) x_inrange = true; //Check if (1)x is in range of (2)x
	if(range(x1+size1,x2,x2+size2) == true) x_inrange = true;
	if(range(y1,y2,y2+size2) == true) y_inrange = true; //Check if (1)y is in range of (2)y
	if(range(y1+size1,y2,y2+size2) == true) y_inrange = true;

	if(x_inrange == true && y_inrange == true) return true; //Collision detected
	return false; //No collision detected
}

//Rect hit
BOOL8 RectHit(FLOAT32 x1, FLOAT32 y1, FLOAT32 width1, FLOAT32 height1, FLOAT32 x2, FLOAT32 y2, FLOAT32 width2, FLOAT32 height2)
{
	BOOL8 x_inrange = false, y_inrange = false;
	if(range(x1,x2,x2+width2) == true) x_inrange = true; //Check if (1)x is in range of (2)x
	if(range(x1+width1,x2,x2+width2) == true) x_inrange = true;
	if(range(y1,y2,y2+height2) == true) y_inrange = true; //Check if (1)y is in range of (2)y
	if(range(y1+height1,y2,y2+height2) == true) y_inrange = true;

	if(x_inrange == true && y_inrange == true) return true; //Collision detected
	return false; //No collision detected
}

//Circle hit
BOOL8 CircleHit(FLOAT32 x1, FLOAT32 y1, FLOAT32 radius1, FLOAT32 x2, FLOAT32 y2, FLOAT32 radius2)
{
	if(distance(x1,y2,x2,y2) < radius2-radius1)
	{
		return true; //Collision detected
	}
	return false; //No collision detected
}

}