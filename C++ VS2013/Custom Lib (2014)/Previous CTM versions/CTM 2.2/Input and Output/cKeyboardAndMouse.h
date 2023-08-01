#ifndef CTM_KEYBOARDANDMOUSE_H
#define CTM_KEYBOARDANDMOUSE_H

#include "../Base/Base.h"

namespace ctm
{

/////////////////
//Keyboard and mouse class
class keyboardandmouse
{
public:
	//System
		keyboardandmouse();
		void clear(); //Resets all keys, mouse buttons, the mouse position, and the old mouse preservation state
		void update(); //Updates the duration that keys have been pressed
		void preserveoldmouse(BOOL8 flag) { preserve = flag; } //When set to true the old mouse position will not be updated
	//Get/Set
		UINT32 get_key(UINT32 index) { return keys[index]; }
		INT32 get_x() { return x; }
		INT32 get_y() { return y; }
		INT32 get_oldx() { return oldx; }
		INT32 get_oldy() { return oldy; }
		void set_key(UINT32 index, BOOL8 state) { if(state == true) ++keys[index]; else keys[index] = 0; }
		void set_mouse(INT32 newx, INT32 newy) { if(preserve == false) { oldx = x; oldy = y; } x = newx; y = newy; }
private:
	UINT32 keys[256]; //Keys and mouse buttons
	INT32 x, y, oldx, oldy; //Mouse position
	bool preserve; //Preserve old mouse flag
};
/////////////////

}

#endif