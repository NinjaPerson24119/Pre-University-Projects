#include "cColor.h"

namespace ctm
{

//Constructor
color::color(FLOAT32 iRed, FLOAT32 iGreen, FLOAT32 iBlue, FLOAT32 iAlpha):
red(iRed),
green(iGreen),
blue(iBlue),
alpha(iAlpha) {}

//Operator =
color& color::operator=(color RHS)
{
	red = RHS.red;
	green = RHS.green;
	blue = RHS.blue;
	alpha = RHS.alpha;
	return *this;
}

//Returns a faded color
color color::fade(color fade_to, FLOAT32 decimalpercent)
{
	color temp = *this; //Copy self to temporary color

	temp.red = temp.red - ((temp.red - fade_to.red) * decimalpercent); //Fade colors
	temp.green = temp.green - ((temp.green - fade_to.green) * decimalpercent);
	temp.blue = temp.blue - ((temp.blue - fade_to.blue) * decimalpercent);

	return temp;
}

}