#ifndef BASE
#define BASE

//Define a few constants
const float PI = 3.1415926535897932384626433832795f;
const float DEG_TO_RAD = PI/180;
const float RAD_TO_DEG = 180/PI;

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#include "cPoint.h" //Point class
#include "cColor.h" //Color class
#include "cLine.h" //Line class
#include "cRectangle.h" //Rectangle class
#include "cTriangle.h" //Triangle class
#include "cMatrix.h" //Matrix template
#include "cAngle.h" //Degrees and radians
#include "Extras.h" //Extra useful functions

#endif