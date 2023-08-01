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
		void preserveoldmouse(bool flag) { preserve = flag; } //When set to true the old mouse position will not be updated
	//Get/Set
		unsigned int get_key(unsigned int index) { return keys[index]; }
		int get_x() { return x; }
		int get_y() { return y; }
		int get_oldx() { return oldx; }
		int get_oldy() { return oldy; }
		void set_key(unsigned int index, bool state) { if(state == true) ++keys[index]; else keys[index] = 0; }
		void set_mouse(int newx, int newy) { if(preserve == false) { oldx = x; oldy = y; } x = newx; y = newy; }
private:
	unsigned int keys[256]; //Keys and mouse buttons
	int x, y, oldx, oldy; //Mouse position
	bool preserve; //Preserve old mouse flag
};
/////////////////

}

#endif