#ifndef MAP_H
#define MAP_H

#include "cMatrix.h"

#ifndef FSTREAM
#define FSTREAM
#include <fstream>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif

/*
* The file format used for saving and loading is up to the user. The extension used is ".mtx", which stands for "Matrix - MaTriX" 
*
* At the beggining of the file is a header that consists of 2 numbers each ending with an x, these numbers
* are the matrix width and height.
*
* After the header is read, the matrix contents follow.
* Every 2 digits on a line represents a number within the range of 0-99
* The digits appear in a grid format but with no spaces. The header is the only information used when reading the matrix.
*
* 4X4 matrix example:
* 4 //Width
* 4 //Height
* 01992078 //Matrix data
* 06200102
* 03441009
* 90807060
*/

//Warning: Errors occur when trying to make a pointer to a map
//Loading not working

///////////////////////
//Map class
class map
{
public:
	map(int width, int height);
	map(std::string filename);
	void reset_map(int width, int height); //Resets the map
	void load_map(std::string filename); //Loads map 
	void save_map(std::string filename); //Saves map
	void set_map(int x, int y, int value) { { if(value < 0) value = 0; if(value > 99) value = 99; data.set_data(x,y,value); } } //Set a map tile
	int get_map(int x, int y) { return data.get_data(x,y); } //Get a map tile
	int get_width() { return data.get_width(); }
	int get_height() { return data.get_height(); }
private:
	matrix<int> data; //Data
};

//Constructor
map::map(int width = 1, int height = 1):
data(1,1,0) //Make default matrix
{
	reset_map(width,height);
}

map::map(std::string filename):
data(1,1,0) //Make default matrix
{
	load_map(filename);
}

//Reset map
void map::reset_map(int width = 1, int height = 1)
{
	if(width < 1) width = 1; //Matrix must be at least 1X1
	if(height < 1) height = 1; 
	data.resize(width,height,0); //Resize matrix
}

//Load map
void map::load_map(std::string filename)
{
	std::string line; //Holds a line in the file
	std::string number; //Holds an individual number from line
	int width = 0;
	int height = 0;

	std::ifstream file(filename.c_str()); //Open file for reading
		
		//Read dimensions
		std::getline(file,line); 
		width = atoi(line.c_str());
		std::getline(file,line);
		height = atoi(line.c_str());
		
		//Resize matrix based on loaded dimensions
		reset_map(width,height);

		//Read matrix data
		for(int y = 0; y < height; y++) //Scroll file
		{
			std::getline(file,line);
			for(int x = 1; x < width+1; x++) //+1 for reading 1 to WIDTH instead of 0 to WIDTH-1
			{
				//Get number
				number.push_back(line.at(x*2-1-1)); //Tens digit
				number.push_back(line.at(x*2-1)); //Ones digit

				//Set number
				data.set_data(x-1,y,atoi(number.c_str())); //-1 because matrix range is 0 to WIDTH-1

				//Reset number
				number.clear();
			}
		}

	file.close();
}

//Save map
void map::save_map(std::string filename)
{
	std::ofstream file(filename.c_str()); //Open file for writing
			
		//Write dimensions
		file << data.get_width() << "\n"; //Write width
		file << data.get_height() << "\n"; //Write height
	
		//Write matrix data
		for(int y = 0; y < data.get_height(); y++) //Scroll matrix
		{
			for(int x = 0; x < data.get_width(); x++)
			{
				if(data.get_data(x,y) < 10) file << 0; //Add zero to numbers below 10
				file << data.get_data(x,y); //Write number
			}
			file << "\n"; //Next line
		}

	file.close(); //Close file
}
///////////////////////

#endif