#include "cMouse.h"

//Constructor
mouse::mouse():
left(false),
right(false),
middle(false) {}

//Flip button
void mouse::flip_button(INT32 which)
{
	switch(which)
	{
	case 0:
		if(left == true) left = false; else left = true;
		break;
	case 1:
		if(middle == true) middle = false; else middle = true;
		break;
	case 2:
		if(right == true) right = false; else right = true;
		break;
	}
}