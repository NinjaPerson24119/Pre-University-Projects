#ifndef SNAKE_H
#define SNAKE_H

#include "Point.h"
#include "Color.h"
#include "Walls.h"
#include "Goal.h"
#include <vector>

//////
//Snake
class Snake
{
public:
	//Base
		Snake(float X, float Y, unsigned int Length, Color HeadC, Color BodyC);
	//Set
		void Reset(float X, float Y, unsigned int Length);
		void Direction(int VecX, int VecY);
		void Move();
		void Grow();
	//Get
		const std::vector<Point> &GetBody();
		const Point GetDirection();
	//Check
		bool Collision(); //Check for self collision
		bool Collision(Walls &Target) const; //Against walls
		bool Collision(Goal &Target) const; //Against goal
	//Data
		Color headc, bodyc;
private:
		std::vector<Point> body;
		Point vec;
};
//////

#endif