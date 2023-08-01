#ifndef KEYBOARD_H
#define KEYBOARD_H

/////////////////
//Keyboard class
class keyboard
{
public:
	//System
		keyboard();
		void update();
	//Functions
		bool get_key(unsigned char which) { return keys[which]; }
		int get_keytime(unsigned char which) { return time[which]; }
		void set_key(unsigned char which, bool state) { keys[which] = state; }
		void reset_keys();
private:
	//Data
		bool keys[256];
		int time[256];
};

//Constructor
keyboard::keyboard()
{
	reset_keys();
}

//Update
void keyboard::update()
{
	for(unsigned int count = 0; count < 256; count++)
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
	for(int count = 0; count < 256; count++)
	{
		keys[count] = false;
		time[count] = 0;
	}
}
/////////////////

#endif