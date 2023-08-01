#include "cColor.h"

namespace ctm
{

//Constructor
color::color(float iRed, float iGreen, float iBlue, float iAlpha):
red(iRed),
green(iGreen),
blue(iBlue),
alpha(iAlpha) {}

//Returns a faded color
color color::fade(color fade_to, float decimalpercent)
{
	color temp = *this; //Copy self to temporary color

	temp.red = temp.red - ((temp.red - fade_to.red) * decimalpercent); //Fade colors
	temp.green = temp.green - ((temp.green - fade_to.green) * decimalpercent);
	temp.blue = temp.blue - ((temp.blue - fade_to.blue) * decimalpercent);

	return temp;
}

}