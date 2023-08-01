#include "Snake.h"

//Constructor
Snake::Snake(float X, float Y, unsigned int Length, Color Head, Color Body):
headc(Head),
bodyc(Body)
{
	Reset(X, Y, Length);
}

//Reset
void Snake::Reset(float X, float Y, unsigned int Length)
{
	//Rebuild snake
	body.clear();
	for(unsigned int count = 0; count < Length; ++count)
	{
		body.push_back(Point(X, Y - count));
	}
	
	//Reset direction
	vec.x = 0.f;
	vec.y = -1.f;
}

//Direction
void Snake::Direction(int VecX, int VecY)
{
	if(VecY == 0)
	{
		if(VecX != -1 * vec.x)
		{
			vec.x = (float)VecX;
			vec.y = (float)VecY;
		}
	}
	
	if(VecX == 0)
	{
		if(VecY != -1 * vec.y)
		{
			vec.x = (float)VecX;
			vec.y = (float)VecY;
		}
	}
}

//Move
void Snake::Move()
{
	for(unsigned int count = body.size() - 1; count != 0; --count)
	{
		body.at(count) = body.at(count - 1);
	}
	body.at(0).x += vec.x;
	body.at(0).y += vec.y;
}

//Grow
void Snake::Grow()
{
	body.push_back(body.at(body.size() - 1));
}

//Get Body
const std::vector<Point> &Snake::GetBody()
{
	return body;
}

//Get Direction
const Point Snake::GetDirection()
{
	return vec;
}

//Collision
bool Snake::Collision()
{
	for(unsigned int count = 1; count < body.size(); ++count)
	{
		if((body.at(0).x == body.at(count).x) && (body.at(0).y == body.at(count).y))
			return true;
	}
	return false;
}

bool Snake::Collision(Walls &Target) const
{
	for(unsigned int count = 0; count < Target.Get().size(); ++count)
	{
		if((Target.Get().at(count).x == body.at(0).x) && (Target.Get().at(count).y == body.at(0).y))
			return true;
	}
	return false;
}

bool Snake::Collision(Goal &Target) const
{
	for(unsigned int count = 0; count < body.size(); ++count)
	{
		if((Target.x == body.at(count).x) && (Target.y == body.at(count).y))
			return true;
	}
	return false;
}