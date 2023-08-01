#ifndef RECTANGLE_H
#define RECTANGLE_H

////////////////////////
//Rectangle class
class rect
{
public:
	rect(float iLeft, float iTop, float iRight, float iBottom); 
	float get_width() { return right-left; }
	float get_height() { return bottom-top; }
	float left, top, right, bottom;
};

//Constructor
rect::rect(float iLeft, float iTop, float iRight, float iBottom):
left(iLeft),
top(iTop),
right(iRight),
bottom(iBottom) {}
////////////////////////

#endif