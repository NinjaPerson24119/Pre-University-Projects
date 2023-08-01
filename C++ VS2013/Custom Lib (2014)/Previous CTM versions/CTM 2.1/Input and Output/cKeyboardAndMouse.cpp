#include "cKeyboardAndMouse.h"

namespace ctm
{
	//Constructor
	keyboardandmouse::keyboardandmouse()
	{
		clear();
	}

	//Clear
	void keyboardandmouse::clear()
	{
		//Reset keys and mouse buttons
		for(UINT32 count = 0; count < 256; ++count)
		{
			keys[count] = 0;
		}

		//Reset mouse position
		x = 0;
		y = 0;
		oldx = 0;
		oldy = 0;

		//Reset preserve
		preserve = false;
	}

	//Update
	void keyboardandmouse::update()
	{
		//Update keys and mouse buttons
		for(UINT32 count = 0; count < 256; ++count)
		{
			if(keys[count] != 0)
				++keys[count];
		}
	}
}