#ifndef WALLS_H
#define WALLS_H

#include "Point.h"
#include "Color.h"
#include "Goal.h"
#include <vector>

//////
//Walls
class Walls
{
public:
	//Base
		Walls(unsigned int Width, unsigned int Height, Color C);
	//Get
		const std::vector<Point> &Get();
	//Check
		bool Collision(Goal &Target);
	//Data
		Color c;
private:
		std::vector<Point> walls;
};
//////

#endif