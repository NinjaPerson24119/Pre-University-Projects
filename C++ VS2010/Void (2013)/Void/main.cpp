//Void- Aliens are attacking earth! You are earth's last line of defence... can you survive the swarm?
//Made by Nicholas Wengel

//V1: (MAY 17 2013)
//-Player movement
//-Single round working gun
//-Self operating physics system (Need only object creation and operate() int mainloop)

#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>

//Set map size
int const mSIZEX = 21-1;
int const mSIZEY = 21-1;

#include "Keyboard(V2).h"//Sets up keyboard
#include "cWorld(V3).h"
#include "ship.h"
#include "even_odd.h"

//Function predeclarations
int get_closex(ship enemies[17]);
int get_farx(ship enemies[17]);
int get_fary(ship enemies[17]);

int main()
{
	//Setup
	srand(time(0)); //Seed randomizer
	world earth; //World

	ship player(mSIZEY/2,mSIZEY*0.75,false,1,&earth,FRIENDLY); //Player
	ship enemies[17] = //Build enemies
	{
		ship(2,1,false,190,&earth,HOSTILE),
		ship(4,1,false,190,&earth,HOSTILE),
		ship(6,1,false,190,&earth,HOSTILE),
		ship(8,1,false,190,&earth,HOSTILE),
		ship(10,1,false,190,&earth,HOSTILE),
		ship(12,1,false,190,&earth,HOSTILE),
		ship(14,1,false,190,&earth,HOSTILE),
		ship(16,1,false,190,&earth,HOSTILE),
		ship(18,1,false,190,&earth,HOSTILE),
		ship(17,2,false,190,&earth,HOSTILE),
		ship(15,2,false,190,&earth,HOSTILE),
		ship(13,2,false,190,&earth,HOSTILE),
		ship(11,2,false,190,&earth,HOSTILE),
		ship(9,2,false,190,&earth,HOSTILE),
		ship(7,2,false,190,&earth,HOSTILE),
		ship(5,2,false,190,&earth,HOSTILE),
		ship(3,2,false,190,&earth,HOSTILE)
	};
	int farx = 0; //Used to hold data from enemy ships
	int closex = 0;
	int fary = 0; //If even move left else move right
	bool moved_down = false; //Check if enemies just moved down
	int startwait = 10; //Time in between enemy moves
	int firerate = 50;
	int dead_enemies = 0; //Counter for dead enemies
	int wait = startwait;
	enum DIRECTION { DLEFT, DRIGHT, DUP, DDOWN, STATIC };
	DIRECTION direction = DRIGHT; //Holds left or right for performance (Less operators in for loop)

	enum GAMESTATE { WAITING, LOSE, WIN };
	GAMESTATE gamestate = WAITING; 

	while(1) //Main loop
	{
		switch(keystate()) //Keyboard input
		{
		case LEFT:
			if(player.get_dead() == false) player.add_vector(-1,0);
			break;
		case RIGHT:
			if(player.get_dead() == false) player.add_vector(1,0);
			break;
		case SPACE:
			if(player.get_dead() == false) player.gun.fire(player.type);
			break;
		default:
			break;
		}

		//Physics
		if(player.x + player.d.dx > mSIZEX) player.set_vector(0,0); //Right wall
		if(player.x + player.d.dx < 0) player.set_vector(0,0); //Left wall
		player.ship_operate(); //Operate player

		for(int count = 0; count < 17; count++) //Enemy data retrieving and action queuing 
		{
			closex = get_closex(enemies); //Get coordinates
			farx = get_farx(enemies);
			fary = get_fary(enemies);
			if(wait == 0) if(moved_down == false) if(farx == mSIZEX) direction = DDOWN; //Check for fire canceling
			if(wait == 0) if(moved_down == false) if(closex == 0) direction = DDOWN; 
			if(direction != DDOWN) if(enemies[count].get_dead() == false) if(rand()%firerate == 0) enemies[count].gun.fire(enemies[count].type); //Send fire action
		}
		if(wait == 0) if(direction != DDOWN) if(even_odd(fary) == EVEN)  direction = DRIGHT; else direction = DLEFT; //If not moving down move on x axis

		for(int count = 0; count < 17; count++) //Enemy actions execution
		{
			if(wait == 0)
			{
				switch(direction)
				{
				case DDOWN:
					enemies[count].set_vector(0,1);
					moved_down = true;
					break;
				case DLEFT:
					enemies[count].set_vector(-1,0);
					moved_down = false;
					break;
				case DRIGHT:
					enemies[count].set_vector(1,0);
					moved_down = false;
					break;
				}
			}
			enemies[count].round_hit_ship(&player); //Enable ship destruction
			player.round_hit_ship(&enemies[count]);
			enemies[count].ship_operate(); //Operate ships
		}
		direction = STATIC; //Decelerate direction
		if(wait == 0) wait = startwait;
		wait--;

		//Check for losing via enemy too low
		if(fary == player.y-1) gamestate = LOSE;
		if(player.get_dead() == true) gamestate = LOSE; //Lose if you die

		//Check winning
		if(gamestate != LOSE)
		{
			dead_enemies = 0; //Reset
			for(int count = 1; count < 17; count++)
			{
				if(enemies[count].get_dead() == true) dead_enemies++;
			}
			if(dead_enemies == 16) gamestate = WIN;
		}

		//Graphical
		earth.draw(1,'0'); //Draw world
		earth.reset(' '); //Clear world

		//LOSING/WINING
		if(gamestate == LOSE) 
		{
			std::cout << "YOU LOSE" << "\n";
			while(keystate() == 0) {} //Wait for keypress
			return 0;
		}
		if(gamestate == WIN) 
		{ 
			std::cout << "YOU WIN" << "\n"; 
			while(keystate() == 0) {} //Wait for keypress 
			return 0;
		}

		system("cls"); //Clear screen
	}
}

//Far coordinate get commands
int get_closex(ship enemies[17])
{
	int closex = mSIZEX;
	for(int count = 0; count < 17; count++)
	{
		if(enemies[count].get_dead() != true)
			if(enemies[count].x < closex) closex = enemies[count].x;
	}
	return closex;
}

int get_farx(ship enemies[17])
{
	int farx = 0;
	for(int count = 0; count < 17; count++)
	{
		if(enemies[count].get_dead() != true)
			if(enemies[count].x > farx) farx = enemies[count].x;
	}
	return farx;
}

int get_fary(ship enemies[17])
{
	int fary = 0;
	for(int count = 0; count < 17; count++)
	{
		if(enemies[count].get_dead() != true)
			if(enemies[count].y > fary) fary = enemies[count].y; 
	}
	return fary;
}