#ifndef CTM_CMDMENU_H
#define CTM_CMDMENU_H

#include <string>
#include <vector>

namespace ctm
{

//////
//Command prompt menu
class cmdmenu
{
public:
	//Constructor
		cmdmenu(const char *Title, const char *Cursor);
		cmdmenu();
	//Run
		size_t run(); //Runs the menu until a choice is made
	//Cursor
		void cursor(const char *Cursor); //Sets the cursor
	//Title
		void title(const char *Title); //Sets the title
	//Add choice
		void add_choice(const char *Choice); //Adds a choice to the menu
private:
	//Update
		void update(); //Updates the menu
	//Draw
		void draw(); //Draws the menu
	bool endrun; //Stop running the menu?
	size_t current; //Current choice selected
	std::string tit; //Title
	std::string cur; //Cursor
	std::vector<std::string> choices; //Choices
};
//////

}

#endif