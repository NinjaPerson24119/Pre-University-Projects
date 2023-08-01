#include "Random.h"
#include <cstdlib>

//Seed
void Random::Seed(unsigned int S)
{
	srand(S);
}

//Get
int Random::Get()
{
	return rand();
}