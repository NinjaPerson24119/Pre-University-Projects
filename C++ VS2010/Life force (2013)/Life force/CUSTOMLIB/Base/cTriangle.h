#ifndef TRIANGLE_H
#define TRIANGLE_H

//////////////////
//Triangle class
class triangle
{
public:
	triangle(float X1, float Y1, float X2, float Y2, float X3, float Y3);
	float x1,y1,x2,y2,x3,y3;
};

//Constructor
triangle::triangle(float X1, float Y1, float X2, float Y2, float X3, float Y3):
x1(X1), y1(Y1),
x2(X2), y2(Y2),
x3(X3), y3(Y3) {}
//////////////////

#endif