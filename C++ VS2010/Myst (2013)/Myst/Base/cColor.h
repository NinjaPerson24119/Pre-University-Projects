#ifndef COLOR_H
#define COLOR_H

//////////////////////////////////////
//Color class
class color
{
public:
	color(float iRed, float iGreen, float iBlue, float iAlpha);
	color& operator=(color RHS);
	color fade(color fade_to, float percent); //Returns a faded color
	float red, green, blue, alpha;
};
//Constructor
color::color(float iRed, float iGreen, float iBlue, float iAlpha = 1.f):
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
color color::fade(color fade_to, float percent)
{
	color temp = *this; //Copy self to temporary color
	percent = percent/100; //Convert percent to decimal

	temp.red = temp.red - ((temp.red - fade_to.red) * percent); //Fade colors
	temp.green = temp.green - ((temp.green - fade_to.green) * percent);
	temp.blue = temp.blue - ((temp.blue - fade_to.blue) * percent);

	return temp;
}
//////////////////////////////////////

#endif