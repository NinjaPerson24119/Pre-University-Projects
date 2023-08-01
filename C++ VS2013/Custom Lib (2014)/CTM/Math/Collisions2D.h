#ifndef CTM_COLLISIONS2D_H
#define CTM_COLLISIONS2D_H

#include "../Base/Base.h"

namespace ctm
{

bool LineHit1D(float a1, float a2, float b1, float b2); //One dimensional line hit
bool BlockHit(float x1, float y1, float size1, float x2, float y2, float size2); //Block hit
bool RectHit(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2); //Rect hit
bool CircleHit(float x1, float y1, float radius1, float x2, float y2, float radius2); //Circle hit

}

#endif