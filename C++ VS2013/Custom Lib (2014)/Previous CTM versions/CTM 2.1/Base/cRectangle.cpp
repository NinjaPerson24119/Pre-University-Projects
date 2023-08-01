#include "cRectangle.h"

namespace ctm
{

//Constructor
rect::rect():
left(0),
top(0),
right(0),
bottom(0) {}

rect::rect(FLOAT32 iLeft, FLOAT32 iTop, FLOAT32 iRight, FLOAT32 iBottom):
left(iLeft),
top(iTop),
right(iRight),
bottom(iBottom) {}

}