#ifndef BASE
#define BASE

//Define primitive types
#include "cTypes.h" //Type definitions

//Define a few constants
namespace ctm
{

const FLOAT32 PI = 3.1415926535897932384626433832795f;
const FLOAT32 DEG_TO_RAD = PI/180;
const FLOAT32 RAD_TO_DEG = 180/PI;

}

#ifndef ASSERT
#define ASSERT
#include <assert.h>
#endif

//Define the following to enable debugging
//Custom Lib debugging requires that DEFAULT_DEBUGLOG is set to a valid debug logger
#define CUSTOMLIB_DEBUG_FATAL //Enables fatal errors and assertions
#define CUSTOMLIB_DEBUG_FAST //Enables warnings in non-speed critical code
#define CUSTOMLIB_DEBUG_SLOW //Enables warnings in speed critical code

#include "cDebugLog.h" //Debug logger
#include "cPoint.h" //Point class
#include "cColor.h" //Color class
#include "cRectangle.h" //Rectangle class
#include "Extras.h" //Extra useful functions

#endif