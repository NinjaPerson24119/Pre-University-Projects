#include "Sound.h"

namespace ctm
{

//Constructor
sound::sound()
{
	
}

//Copy constructor
sound::sound(sound &rhs)
{

}

//Destructor
sound::~sound()
{

}

//Operator =
sound &sound::operator=(sound &rhs)
{
	return *this;
}

//Load sound
BOOL8 sound::load_sound(string &iWavFilename)
{
	return true;
}

}