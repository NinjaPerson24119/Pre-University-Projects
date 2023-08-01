#include "Walls.h"

//Constructor
Walls::Walls(unsigned int Width, unsigned int Height, Color C):
c(C)
{
	//Create horizontal walls
	for(unsigned int count = 0; count < Width; ++count)
	{
		walls.push_back(Point((float)count, 0));
		walls.push_back(Point((float)count, (float)Height));
	}
	
	//Create vertical walls
	for(unsigned int count = 0; count < Height; ++count)
	{
		walls.push_back(Point(0, (float)count));
		walls.push_back(Point((float)Width, (float)count));
	}
}

//Get
const std::vector<Point> &Walls::Get()
{
	return walls;
}

//Collision
bool Walls::Collision(Goal &Target)
{
	for(unsigned int count = 0; count < walls.size(); ++count)
	{
		if((walls.at(count).x == Target.x) && (walls.at(count).y == Target.y))
			return true;
	}
	return false;
}