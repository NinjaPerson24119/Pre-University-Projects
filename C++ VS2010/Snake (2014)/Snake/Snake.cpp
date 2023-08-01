//Snake game clone
//By: Nicholas Wengel
//First successful game!! Made after moving onto C++ after stopping work on 3DGUN (Darkbasic)
//Finished version 1.0 on FEB 28 OF 2013

#include <iostream> //base functions
#include <conio.h> //keyboard recognition
#include <cstdlib> //random numbers
#include <stdlib.h> //system()
#include <Windows.h> //Sleep

//Headers
#include "Keyboard.h" //Keyboard plugin (returns scancode of keys with keystate())
#include "cWorld.h" //Base HUD view (Draws out data to screen based off of its world array)
#include "cDoubleint.h" //Object that holds an x and y coordinate
#include "cSnake.h" //The snake object
#include "cPoint.h" //Placeholder of a point on the screen

//Keys
int const up = 72;
int const down = 80;
int const left = 75;
int const right = 77;
int main()
{
	
	std::cout << "SNAKE GAME\n";
	Sleep(1000);

	//Seed random number generator
	srand(rand());

	//Build map
	world earth;

	//Build snake
	snake player(10,10,1);

	//Build food
	int foodx = rand()%18;
	int foody = rand()%18;

	do
	{
		foodx = rand()%18;
		foody = rand()%18;
	
	} while( (foodx == 0) || (foody == 0) || (player.overlap(foodx, foody) == 1) );

	point food(foodx,foody);

	//Mainloop
	while(1)
	{
		//Movement
		switch(keystate())
		{
		case up:
			if(player.get_direction() != 3)
				player.set_direction(1);
			break;
		case down:
			if(player.get_direction() != 1)
				player.set_direction(3);
			break;
		case left:
			if(player.get_direction() != 2)
				player.set_direction(4);
			break;
		case right:
			if(player.get_direction() != 4)
				player.set_direction(2);
			break;
		}

		//Allow growth
		if( (player.get_headx() == foodx) && (player.get_heady() == foody) )
		{
			player.set_length(player.get_length() + 1); //Enlarge player
			do //Randomize food location
			{
				foodx = rand()%18;
				foody = rand()%18;
			} while( (foodx == 0) || (foody == 0) || (player.overlap(foodx,foody) == 1) );
		}

		player.move(); //Move player

		earth.reset(); //Reset the map
		earth.layout();
		
		//Position food
		earth.set_map(foodx,foody, '+');

		for(int count = 0; count < player.get_length(); count++) //Position body segments
		{
			earth.set_map(player.get_body1(count), player.get_body2(count), 'O');
		}
		earth.set_map(player.get_headx(),player.get_heady(), '@'); //Position head

		earth.draw(); //Draw the map

		//Display snake length
		std::cout << "Snake length:\t" << player.get_length()+1 << "\n";

		//Allow death
		if( (player.get_headx() == 0) || (player.get_headx() == 19) || (player.get_heady() == 0) || (player.get_heady() == 19) || (player.overlap(player.get_headx(), player.get_heady()) == 1) )
		{
			std::cout << "You lose!\n";
			Sleep(4000);
			return 0;
		}

		//Slow down program
		Sleep(50);

		//Clear the screen
		system("cls");

	}

	return 0;
}