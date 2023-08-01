#include "CmdMenu.h"

#include <conio.h>
#include <cstdlib>
#include <iostream>

namespace ctm
{

//Constructor
cmdmenu::cmdmenu(const char *Title, const char *Cursor):
tit(Title),
cur(Cursor),
endrun(false)
{}

cmdmenu::cmdmenu():
cmdmenu("Title", "->")
{}

//Run
size_t cmdmenu::run()
{
	//Reset run state
	endrun = false;

	//Begin loop
	while(!endrun)
	{
		update(); //Update the menu
		draw(); //Draw the menu
	}

	return current; //Return the current cursor position
}

//Cursor
void cmdmenu::cursor(const char *Cursor)
{
	cur = Cursor;
}

//Title
void cmdmenu::title(const char *Title)
{
	tit = Title;
}

//Add choice
void cmdmenu::add_choice(const char *Choice)
{
	choices.push_back(Choice);
}

//Update
void cmdmenu::update()
{
	if(_kbhit())
	{
		switch(_getch())
		{
		case 72: //Up
			--current;
			break;
		case 80: //Down
			++current;
			break;
		case 13: //Enter
			endrun = true;
			break;
		}
	}

	//Wrap cursor
	if(current < 0)
		current = choices.size() - 1;
	if(current >= choices.size())
		current = 0;
}

//Draw
void cmdmenu::draw()
{
	//Clear the console
	system("cls");

	//Draw title
	std::cout << tit.c_str() << "\n";

	//Cycle choices
	for(size_t count = 0; count < choices.size(); ++count)
	{
		//Draw cursor
		if(count == current)
			std::cout << cur.c_str();
		
		//Draw choice
		std::cout << choices.at(count).c_str() << "\n";
	}
}

}