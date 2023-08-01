#include "cKeyboard.h"

//Constructor
keyboard::keyboard()
{
	reset_keys();
}

//Update
void keyboard::update()
{
	for(UINT32 count = 0; count < 256; count++)
	{
		if(keys[count] == true)
			time[count]++;
		else
			time[count] = 0;
	}
}

//Reset keys
void keyboard::reset_keys()
{
	//Set all keys to false
	for(INT32 count = 0; count < 256; count++)
	{
		keys[count] = false;
		time[count] = 0;
	}
}