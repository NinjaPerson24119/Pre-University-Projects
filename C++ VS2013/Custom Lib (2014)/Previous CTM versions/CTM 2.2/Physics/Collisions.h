#ifndef CTM_COLLISIONS_H
#define CTM_COLLISIONS_H

#include "../Base/Base.h"

namespace ctm
{

bool LineHit1D(FLOAT32 a1, FLOAT32 a2, FLOAT32 b1, FLOAT32 b2); //One dimensional line hit
bool BlockHit(FLOAT32 x1, FLOAT32 y1, FLOAT32 size1, FLOAT32 x2, FLOAT32 y2, FLOAT32 size2); //Block hit
bool RectHit(FLOAT32 x1, FLOAT32 y1, FLOAT32 width1, FLOAT32 height1, FLOAT32 x2, FLOAT32 y2, FLOAT32 width2, FLOAT32 height2); //Rect hit
bool CircleHit(FLOAT32 x1, FLOAT32 y1, FLOAT32 radius1, FLOAT32 x2, FLOAT32 y2, FLOAT32 radius2); //Circle hit

}

#endif