#include "Collisions2D.h"
#include "MathGeneralFunctions.h"

namespace ctm
{

//One dimensional line hit
bool LineHit1D(float a1, float a2, float b1, float b2)
{
	if((a1 > b1) && (a1 < b2)) return true;
	if((a2 > b1) && (a2 < b2)) return true;
	return false;
}

//Block hit
bool BlockHit(float x1, float y1, float size1, float x2, float y2, float size2)
{
	bool x_inrange = false, y_inrange = false;
	if(inrange(x1,x2,x2+size2) == true) x_inrange = true; //Check if (1)x is in range of (2)x
	if(inrange(x1+size1,x2,x2+size2) == true) x_inrange = true;
	if(inrange(y1,y2,y2+size2) == true) y_inrange = true; //Check if (1)y is in range of (2)y
	if(inrange(y1+size1,y2,y2+size2) == true) y_inrange = true;

	if(x_inrange == true && y_inrange == true) return true; //Collision detected
	return false; //No collision detected
}

//Rect hit
bool RectHit(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2)
{
	bool x_inrange = false, y_inrange = false;
	if(inrange(x1,x2,x2+width2) == true) x_inrange = true; //Check if (1)x is in range of (2)x
	if(inrange(x1+width1,x2,x2+width2) == true) x_inrange = true;
	if(inrange(y1,y2,y2+height2) == true) y_inrange = true; //Check if (1)y is in range of (2)y
	if(inrange(y1+height1,y2,y2+height2) == true) y_inrange = true;

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

}