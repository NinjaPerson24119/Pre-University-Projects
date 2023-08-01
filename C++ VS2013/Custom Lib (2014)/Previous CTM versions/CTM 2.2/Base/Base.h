#ifndef CTM_BASE
#define CTM_BASE

#include "cTypes.h" //Type definitions

//Define a few constants
namespace ctm
{

extern const FLOAT32 PI;
extern const FLOAT32 DEG_TO_RAD;
extern const FLOAT32 RAD_TO_DEG;

}

#include "cDebugLog.h" //Debug logger
#include "cPoint.h" //Point class
#include "cColor.h" //Color class
#include "cRectangle.h" //Rectangle class
#include "Extras.h" //Extra useful functions
#include "ReadyCheck.h" //Function to check that Custom Lib is ready for use

#endif