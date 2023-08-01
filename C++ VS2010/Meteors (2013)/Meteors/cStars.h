#ifndef STARS_H
#define STARS_H

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

////////////////////////
//Stars class
class stars
{
public:
	stars(float X1, float Y1, float X2, float Y2, int starcount, color iBrush);
	void draw(); //Draw
	void randomize(); //Randomize stars
	void set_color(color nBrush) { brush = nBrush; } //Set color
private:
	std::vector<point> locations; //Star locations
	color brush; //Star color
	float x1, y1, x2, y2; //Star boundaries
};

//Constructor
stars::stars(float X1, float Y1, float X2, float Y2, int starcount, color iBrush):
locations(starcount,point(0,0)),
brush(iBrush),
x1(X1), y1(Y1),
x2(X2), y2(Y2)
{
	randomize();
}

//Draw
void stars::draw()
{
	for(unsigned int count = 0; count < locations.size(); count++)
	{
		DrawPoint(locations.at(count).x,locations.at(count).y,brush);
	}
}

//Randomize stars
void stars::randomize()
{
	for(unsigned int count = 0; count < locations.size(); count++)
	{
		locations.at(count).x = (rand()%(int)(x2-x1))+x1;
		locations.at(count).y = (rand()%(int)(y2-y1))+y1;
	}
}
////////////////////////

#endif