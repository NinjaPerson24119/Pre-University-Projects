#ifndef KEYBOARD_H
#define KEYBOARD_H

/////////////////
//Keyboard class
class keyboard
{
public:
	//System
		keyboard();
		void update(unsigned char key);
	//Functions
		bool get_key(unsigned char which) { return keys[which]; }
		void set_key(unsigned char which, bool state) { keys[which] = state; }
		void reset_keys();
private:
	//Data
		bool keys[256];
};

//Constructor
keyboard::keyboard()
{
	reset_keys();
}

//Update
void keyboard::update(unsigned char key)
{
	//Change key states
	if(keys[key] == false) 
		keys[key] = true; 
	else 
		keys[key] = false;
}

//Reset keys
void keyboard::reset_keys()
{
	//Set all keys to false
	for(int count = 0; count < 256; count++)
	{
		keys[count] = false;
	}
}
/////////////////

#endif