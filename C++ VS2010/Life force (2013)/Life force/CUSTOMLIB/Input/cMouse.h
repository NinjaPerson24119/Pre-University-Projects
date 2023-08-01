#ifndef MOUSE_H
#define MOUSE_H

////////////////////////
//Mouse class
class mouse
{
public:
	//System
		mouse();
	//Commands
		void flip_button(int which);
		void set_button(int which, bool state) { if(which == 0) left = state; if(which == 1) middle = state; if(which == 2) right = state; }
		bool get_button(int which) { if(which == 0) return left; if(which == 1) return middle; if(which == 2) return right; return false; }
	//Cursor
		point position;
		point last_position;
private:
	//Buttons
		bool left;
		bool right;
		bool middle;
};

//Constructor
mouse::mouse():
left(false),
right(false),
middle(false) {}

//Flip button
void mouse::flip_button(int which)
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
////////////////////////

#endif