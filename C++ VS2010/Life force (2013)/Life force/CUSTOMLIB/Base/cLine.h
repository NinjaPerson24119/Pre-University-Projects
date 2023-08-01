#ifndef LINE_H
#define LINE_H

///////////////////
//Line class
class line
{
public:
	line(float X1, float Y1, float X2, float Y2);
	float x1,y1,x2,y2;
};

//Constructor
line::line(float X1, float Y1, float X2, float Y2):
x1(X1), y1(Y1),
x2(X2), y2(Y2) {}
///////////////////

#endif