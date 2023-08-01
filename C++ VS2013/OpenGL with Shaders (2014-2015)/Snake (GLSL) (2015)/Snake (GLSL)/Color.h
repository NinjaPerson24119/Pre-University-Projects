#ifndef COLOR_H
#define COLOR_H

//////
//Color
class Color
{
public:
	//Base
		Color();
		Color(float R, float G, float B, float A = 1.f);
	//Set
		void SetColor(float R, float G, float B, float A = 1.f);
	//Data
		float r, g, b, a;
};
//////

#endif