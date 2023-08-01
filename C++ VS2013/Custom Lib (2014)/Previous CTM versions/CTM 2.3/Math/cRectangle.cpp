#include "cRectangle.h"

namespace ctm
{

//Constructor
rect::rect():
left(0),
top(0),
right(0),
bottom(0) {}

rect::rect(float iLeft, float iTop, float iRight, float iBottom):
left(iLeft),
top(iTop),
right(iRight),
bottom(iBottom) {}

}