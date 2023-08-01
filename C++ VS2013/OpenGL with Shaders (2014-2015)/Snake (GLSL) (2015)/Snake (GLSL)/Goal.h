#ifndef GOAL_H
#define GOAL_H

#include "Color.h"

//////
//Goal
class Goal
{
public:
	//Base
		Goal(int MinX, int MinY, int MaxX, int MaxY);
	//Set
		void Randomize();
	//Data
		float x, y;
		Color c;
private:
		int minx, miny, maxx, maxy;
};
//////

#endif