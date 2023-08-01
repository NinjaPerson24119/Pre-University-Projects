#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../Base/Base.h"

/////////////////
//Keyboard class
class keyboard
{
public:
	//System
		keyboard();
		void update();
	//Functions
		BOOL8 get_key(UCHAR8 which) { return keys[which]; }
		INT32 get_keytime(UCHAR8 which) { return time[which]; }
		void set_key(UCHAR8 which, BOOL8 state) { keys[which] = state; }
		void reset_keys();
private:
	//Data
		BOOL8 keys[256];
		INT32 time[256];
};
/////////////////

#endif