#ifndef CTM_COLOR_H
#define CTM_COLOR_H

#include "../Base/Base.h"

namespace ctm
{

//////////////////////////////////////
//Color class
class color
{
public:
	color(float iRed, float iGreen, float iBlue, float iAlpha = 1.f);
	color fade(color fade_to, float decimalpercent); //Returns a faded color
	float red, green, blue, alpha;
};
//////////////////////////////////////

}

#endif