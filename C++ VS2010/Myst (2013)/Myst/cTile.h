#ifndef TILE_H
#define TILE_H

#ifndef STRING
#define STRING
#include <string>
#endif

#ifndef FSTREAM
#define FSTREAM
#include <fstream>
#endif

/////////////////////
//Tile class
class tile
{
public:
	//System
		tile();
		tile(std::string filename);
		void load_tile(std::string filename);
		void save_tile(std::string filename);
	//Data
		std::string name; //Name of tile
		bool walkable; //Can land based characters occupy this tile
		int movement_cost; //Cost to travel on tile
		int hitchance_bonus; //Hitchance bonus for occupant
		int defense_bonus; //Defense bonus for occupant
		int health_bonus; //Health bonus for occupant (Positive will give health and negative will take health)
};

//Constructor
tile::tile():
walkable(true),
movement_cost(0),
hitchance_bonus(0),
defense_bonus(0),
health_bonus(0) {}

tile::tile(std::string filename):
walkable(true),
movement_cost(0),
hitchance_bonus(0),
defense_bonus(0),
health_bonus(0) 
{
	load_tile(filename);
}

//Load tile
void tile::load_tile(std::string filename)
{
	std::ifstream file(filename); //Open file for reading
		std::string line; //Temporary string to hold file lines
		
		//Walkable
		std::getline(file,line);
		if(atoi(line.c_str()) == 1)
			walkable = true;
		else
			walkable = false;

		//Movement cost
		std::getline(file,line);
		movement_cost = atoi(line.c_str());

		//Hitchance bonus
		std::getline(file,line);
		hitchance_bonus = atoi(line.c_str());

		//Defense bonus
		std::getline(file,line);
		defense_bonus = atoi(line.c_str());

		//Health bonus
		std::getline(file,line);
		health_bonus = atoi(line.c_str());

	file.close(); //Close file
}

//Save tile
void tile::save_tile(std::string filename)
{
	std::ofstream file(filename); //Open file for writing
		file << name << "\n"; //Name
		if(walkable == true) file << 1 << "\n"; else file << 0 << "\n"; //Walkable
		file << movement_cost << "\n"; //Movement cost
		file << hitchance_bonus << "\n"; //Hitchance bonus
		file << defense_bonus << "\n"; //Defense bonus
		file << health_bonus << "\n"; //Health bonus
	file.close(); //Close file
}
/////////////////////

#endif