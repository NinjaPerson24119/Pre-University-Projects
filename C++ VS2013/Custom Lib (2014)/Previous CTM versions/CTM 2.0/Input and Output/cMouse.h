#ifndef MOUSE_H
#define MOUSE_H

#include "../Base/Base.h"

////////////////////////
//Mouse class
class mouse
{
public:
	//System
		mouse();
	//Commands
		void flip_button(INT32 which);
		void set_button(INT32 which, BOOL8 state) { if(which == 0) left = state; if(which == 1) middle = state; if(which == 2) right = state; }
		BOOL8 get_button(INT32 which) { if(which == 0) return left; if(which == 1) return middle; if(which == 2) return right; return false; }
	//Cursor
		point position;
		point last_position;
private:
	//Buttons
		BOOL8 left, right, middle;
};
////////////////////////

#endif