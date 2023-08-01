#ifndef EXTRAS_H
#define EXTRAS_H

#include "Base.h"

namespace ctm
{

BOOL8 range(FLOAT32 num, FLOAT32 lowest, FLOAT32 highest); //Checks if a number is within a range
FLOAT32 distance(FLOAT32 x1, FLOAT32 y1, FLOAT32 x2, FLOAT32 y2); //Returns distance between two points
UINT32 lowestpow2(UINT32 min); //Finds the lowest power of two a number can fit in

}

#endif