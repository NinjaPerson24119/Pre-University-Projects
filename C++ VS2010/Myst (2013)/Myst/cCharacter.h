#ifndef CHARACTER_H
#define CHARACTER_H

#ifndef STRING
#define STRING
#include <string>
#endif

#ifndef FSTREAM
#define FSTREAM
#include <fstream>
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

//////////////////
//Character class
class character
{
public:
	//System
		character();
		character(std::string filename);
		~character();
		void load_character(std::string filename);
		void save_character(std::string filename);
	//Data
		//Physical
			float x, y; //Position
			std::vector<animation*> anims; //Animations (Static, Move, Attack, Die, Damaged)
		//Class
			std::string name; //Name of character
			bool friendly; //Team
		//Stats
			int maxhealth; //Starting health points / Maximum health points
			int health; //Health points remaining
			int maxmovement; //Starting movement points
			int movement; //Movement points remaining
			int speed; //Affects movement points and how many times you attack in combat
			int agility; //Makes you harder to hit
			int strength; //Makes you deal more damage
		//Leveling
			int level; //Current level
			int maxexperience; //Experience needed to level up
			int experience; //Experience
};

//Constructor
character::character():
x(0),
y(0),
maxhealth(0),
health(0),
maxmovement(0),
movement(0),
speed(0),
agility(0),
strength(0),
level(0),
maxexperience(0),
experience(0) {}

character::character(std::string filename):
x(0),
y(0),
maxhealth(0),
health(0),
maxmovement(0),
movement(0),
speed(0),
agility(0),
strength(0),
level(0),
maxexperience(0),
experience(0) 
{
	load_character(filename);
}

//Destructor
character::~character()
{
	//Delete animations if existant
	for(unsigned int count = 0; count < anims.size(); count++)
	{
		if(anims.at(count) != 0) delete anims.at(count);
		anims.at(count) = 0;
	}
}

//Load character
void character::load_character(std::string filename)
{
	std::ifstream file(filename); //Open file for reading
		std::string line; //String to hold line contents

		std::getline(file,line); //X
		x = (float)atoi(line.c_str());

		std::getline(file,line); //Y
		y = (float)atoi(line.c_str());

		std::getline(file,line); //Name
		name = line;

		std::getline(file,line); //Team
		if(atoi(line.c_str()) == 1)
			friendly = true;
		else
			friendly = false;

		std::getline(file,line); //Max health
		maxhealth = atoi(line.c_str());

		std::getline(file,line); //Health
		health = atoi(line.c_str());

		std::getline(file,line); //Max movement
		maxmovement = atoi(line.c_str());

		std::getline(file,line); //Movement
		movement = atoi(line.c_str());

		std::getline(file,line); //Speed
		speed = atoi(line.c_str());

		std::getline(file,line); //Agility
		agility = atoi(line.c_str());

		std::getline(file,line); //Strength
		strength = atoi(line.c_str());

		std::getline(file,line); //Level
		level = atoi(line.c_str());

		std::getline(file,line); //Max experience
		maxexperience = atoi(line.c_str());

		std::getline(file,line); //Experience
		experience = atoi(line.c_str());
	
	file.close(); //Close file
}

//Save character
void character::save_character(std::string filename)
{
	std::ofstream file(filename); //Open file for writing

	file << x << "\n"; //X
	file << y << "\n"; //Y
	file << name << "\n"; //Name
	if(friendly == true) file << 1 << "\n"; else file << 0 << "\n"; //Team
	file << maxhealth << "\n"; //Max health
	file << health << "\n"; //Health
	file << maxmovement << "\n"; //Max movement
	file << movement << "\n"; //Movement
	file << speed << "\n"; //Speed
	file << agility << "\n"; //Agility
	file << strength << "\n"; //Strength
	file << level << "\n"; //Level
	file << maxexperience << "\n"; //Max experience
	file << experience << "\n"; //Experience

	file.close(); //Close file
}
//////////////////

#endif