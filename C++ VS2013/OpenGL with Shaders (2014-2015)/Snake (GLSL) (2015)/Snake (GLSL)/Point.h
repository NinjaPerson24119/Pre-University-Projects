#ifndef POINT_H
#define POINT_H

//////
//Point
class Point
{
public:
	//Base
		Point(float X = 0.f, float Y = 0.f);
	//Set
		void SetPoint(float X, float Y);
	//Data
		float x, y;
};
//////

#endif