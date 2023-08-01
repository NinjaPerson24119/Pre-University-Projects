#include <iostream> //Drawing operations
#include <cstdlib> //Randomizer
#include <ctime> //Clock
#include <stdlib.h> //System commands
#include <conio.h> //Keyboard recognition
#include <Windows.h> //Sleep command

#include "Keyboard.h" //Keyboard recognition
#include "cWorld.h" //World functions for drawing
#include "cPoint.h" //Point class for obstacles
#include "runner.h" //Player class

//Define keys
int const LEFT = 75;
int const RIGHT = 77;

int const hits = 2;

int main()
{
	//Setup colors
	system("color 0A");

	//Starting screen
	std::cout << " --------      |     |       | -------               \n";
	std::cout << " |            | |     |     |  |                     \n";
	std::cout << " |           |---|     |   |   -------               \n";
	std::cout << " |          |     |     | |    |                     \n";
	std::cout << " --------  |       |     |     -------               \n";
	std::cout << "                                                     \n";
	std::cout << " --------   |         | ||    |  | | |               \n";
	std::cout << " |      |   |         | | |   |  | | |               \n";
	std::cout << " |-------   |         | |  |  |  | | |               \n";
	std::cout << " |      |   |         | |   | |                      \n";
	std::cout << " |       |   ---------  |    ||  | | |               \n";
	std::cout << "--------------------------------------               \n";
	system("pause");

	srand(time(0)); //Seed randomizer

	//Initialization
	runner player(10); //Build player
	world earth; //Build world
	point walls[20][hits]; //Build obstacles
	int waves = 0;

	while(1)
	{
		//Setup obstacles
		

		switch(keystate()) //Keyboard movement
		{
		case LEFT:
			player.left();
			break;
		case RIGHT:
			player.right();
			break;
		}

	//Scroll obstacles
		point temp[20][hits]; //Temporary array
		for(int first = 0; first < 20; first++) //Copy data
		{
			for(int second = 0; second < hits; second++)
			{
				temp[first][second] = walls[first][second];
			}
		}

		for(int scrolling = 0; scrolling < 20; scrolling++) //Scroll
		{
			for(int second = 0; second < hits; second++)
			{
				if(scrolling-1 != -1)
				{
					walls[scrolling][second] = temp[scrolling-1][second];
				}
			}
		}
	
		for(int num = 0; num < hits; num++)
		{
			walls[0][num].set_x(rand()%20);
		}

		//Collisions
		if(player.get_x() > 19) player.set_x(19);
		if(player.get_x() < 0) player.set_x(0);

		//Drawing operations
		earth.set_map(player.get_x(), 19 , 1); //Mark player position
		
		//Mark obstacles
		for(int count1 = 0; count1 < 20; count1++)
		{
			for(int count2 = 0; count2 < hits; count2++)
			{
				if( (walls[count1][count2].get_x() < 20) && (walls[count1][count2].get_x() > -1) )
				earth.set_map(walls[count1][count2].get_x(), count1, 31);
			}
		}

		earth.draw();
		earth.reset(' ');

		//Draw score
		waves++;
		std::cout << "SCORE:" << waves << "\n";

		//Allow death
		for(int count = 0; count < hits; count++)
		{
			if(walls[19][count].get_x() == player.get_x())
			{
				std::cout << "YOU LOSE!!!\n";
				Sleep(1000);
				system("pause");
				return 0;
			}
		}


		Sleep(40); //Slowdown game
		system("cls"); //Clear the screen
	}
}