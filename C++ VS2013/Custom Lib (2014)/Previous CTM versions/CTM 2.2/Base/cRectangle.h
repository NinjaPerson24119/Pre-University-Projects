#ifndef CTM_RECTANGLE_H
#define CTM_RECTANGLE_H

#include "Base.h"

namespace ctm
{

////////////////////////
//Rectangle class
class rect
{
public:
	rect();
	rect(FLOAT32 iLeft, FLOAT32 iTop, FLOAT32 iRight, FLOAT32 iBottom); 
	FLOAT32 get_width() { return right-left; }
	FLOAT32 get_height() { return bottom-top; }
	FLOAT32 left, top, right, bottom;
};
////////////////////////

}

#endif