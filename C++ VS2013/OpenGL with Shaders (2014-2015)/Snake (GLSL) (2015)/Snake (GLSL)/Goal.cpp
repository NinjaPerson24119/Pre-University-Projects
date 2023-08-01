#include "Goal.h"
#include "Random.h"
#include <cstdlib>

//Constructor
Goal::Goal(int MinX, int MinY, int MaxX, int MaxY):
minx(MinX),
miny(MinY),
maxx(MaxX),
maxy(MaxY)
{
	c.a = 1.f;
	Randomize();
}

//Randomize
void Goal::Randomize()
{
	x = (float)(Random::Get() % (maxy - minx) + minx);
	y = (float)(Random::Get() % (maxy - miny) + miny);
	c.r = (float)(Random::Get() % 100 / 100);
	c.g = (float)(Random::Get() % 100 / 100);
	c.b = (float)(Random::Get() % 100 / 100);
}