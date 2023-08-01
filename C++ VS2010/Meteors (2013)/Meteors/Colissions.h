#ifndef COLISSIONS
#define COLISSIONS

#ifndef MATH
#define MATH
#include <math.h>
#endif

//Block hit
bool BlockHit(float x1, float y1, float size1, float x2, float y2, float size2)
{
	bool x_inrange = false, y_inrange = false;
	if(range(x1,x2,x2+size2) == true) x_inrange = true; //Check if (1)x is in range of (2)x
	if(range(x1+size1,x2,x2+size2) == true) x_inrange = true;
	if(range(y1,y2,y2+size2) == true) y_inrange = true; //Check if (1)y is in range of (2)y
	if(range(y1+size1,y2,y2+size2) == true) y_inrange = true;

	if(x_inrange == true && y_inrange == true) return true; //Collision detected
	return false; //No collision detected
}

//Rect hit
bool RectHit(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2)
{
	bool x_inrange = false, y_inrange = false;
	if(range(x1,x2,x2+width2) == true) x_inrange = true; //Check if (1)x is in range of (2)x
	if(range(x1+width1,x2,x2+width2) == true) x_inrange = true;
	if(range(y1,y2,y2+height2) == true) y_inrange = true; //Check if (1)y is in range of (2)y
	if(range(y1+height1,y2,y2+height2) == true) y_inrange = true;

	if(x_inrange == true && y_inrange == true) return true; //Collision detected
	return false; //No collision detected
}

//Circle hit
bool CircleHit(float x1, float y1, float radius1, float x2, float y2, float radius2)
{
	if(distance(x1,y2,x2,y2) < radius2-radius1)
	{
		return true; //Collision detected
	}
	return false; //No collision detected
}

//Circle hit without square root
bool CircleHit2(float x1, float y1, float radius1, float x2, float y2, float radius2)
{
	if(distance2(x1,y2,x2,y2) < radius2*radius2-radius1*radius1)
	{
		return true; //Collision detected
	}
	return false; //No collision detected
}

#endif