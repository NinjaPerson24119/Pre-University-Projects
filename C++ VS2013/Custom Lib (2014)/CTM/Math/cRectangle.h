#ifndef CTM_RECTANGLE_H
#define CTM_RECTANGLE_H

#include "../Base/Base.h"

namespace ctm
{

////////////////////////
//Rectangle class
class rect
{
public:
	rect();
	rect(float iLeft, float iTop, float iRight, float iBottom); 
	float get_width() { return right-left; }
	float get_height() { return bottom-top; }
	float left, top, right, bottom;
};
////////////////////////

}

#endif