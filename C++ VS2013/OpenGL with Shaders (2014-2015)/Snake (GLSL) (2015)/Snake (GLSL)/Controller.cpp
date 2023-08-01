#include "Controller.h"

//Constructor
Controller::Controller(bool SingleInput):
singleinput(SingleInput),
x(0),
y(0),
usecoords(false),
up(false),
down(false),
left(false),
right(false)
{}

//Get X
unsigned int Controller::GetX()
{
	return x;
}

//Get Y
unsigned int Controller::GetY()
{
	return y;
}

//Get Coord Usage
bool Controller::GetCoordUsage()
{
	return usecoords;
}

//Get Up
bool Controller::GetUp()
{
	return up;
}

//Get Down
bool Controller::GetDown()
{
	return down;
}

//Get Left
bool Controller::GetLeft()
{
	return left;
}

//Get Right
bool Controller::GetRight()
{
	return right;
}

//Set X
void Controller::SetX(unsigned int X)
{
	x = X;
}

//Set Y
void Controller::SetY(unsigned int Y)
{
	y = Y;
}

//Set Coord Usage
void Controller::SetCoordUsage(bool Use)
{
	usecoords = Use;

	if(singleinput == true)
		if(Use == true)
		{
			up = false;
			down = false;
			left = false;
			right = false;
		}
}

//Set Up
void Controller::SetUp(bool Pressed)
{
	up = Pressed;

	if(singleinput == true)
		if(Pressed == true)
		{
			usecoords = false;
			down = false;
			left = false;
			right = false;
		}
}

//Set Down
void Controller::SetDown(bool Pressed)
{
	down = Pressed;

	if(singleinput == true)
		if(Pressed == true)
		{
			usecoords = false;
			up = false;
			left = false;
			right = false;
		}
}

//Set Left
void Controller::SetLeft(bool Pressed)
{
	left = Pressed;

	if(singleinput == true)
		if(Pressed == true)
		{
			usecoords = false;
			up = false;
			down = false;
			right = false;
		}
}

//Set Right
void Controller::SetRight(bool Pressed)
{
	right = Pressed;

	if(singleinput == true)
		if(Pressed == true)
		{
			usecoords = false;
			up = false;
			down = false;
			left = false;
		}
}