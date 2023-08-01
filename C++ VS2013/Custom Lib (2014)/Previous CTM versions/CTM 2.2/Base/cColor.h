#ifndef CTM_COLOR_H
#define CTM_COLOR_H

#include "Base.h"

namespace ctm
{

//////////////////////////////////////
//Color class
class color
{
public:
	color(FLOAT32 iRed, FLOAT32 iGreen, FLOAT32 iBlue, FLOAT32 iAlpha = 1.f);
	color fade(color fade_to, FLOAT32 decimalpercent); //Returns a faded color
	FLOAT32 red, green, blue, alpha;
};
//////////////////////////////////////

}

#endif