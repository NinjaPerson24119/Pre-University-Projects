#ifndef GAME_H
#define GAME_H

#ifndef STRING
#define STRING
#include <string>
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef FSTREAM
#define FSTREAM
#include <fstream>
#endif

//Map defaults
const float TILE_SIZE = 32;

//Window defaults
const rect MAIN_WINDOW(0,0,640,351);
const color MAIN_WINDOW_FILL(0.94f,0.24f,0.27f);

const rect SECONDARY_WINDOW(0,352,640,480);
const color SECONDARY_WINDOW_FILL(0.34f,0.38f,0.82f);
const color SECONDARY_WINDOW_BORDER(0.25f,0.28f,0.80f);
const float SECONDARY_WINDOW_BORDER_SIZE = 5;

//Keyboard control defaults
const char KEYBOARD_LEFT = 'a';
const char KEYBOARD_RIGHT = 'd';
const char KEYBOARD_UP = 'w';
const char KEYBOARD_DOWN = 's';

//Mouse control defaults
const int MOUSE_DRAG_CAMERA = 2; //Mouse buttons are 0,1,2 (LEFT,MIDDLE,RIGHT)

////////////////////////////
//Game class
class game
{
public:
	//System
		game();
		~game();
		void setup(); //Sets up game
		void update(); //Updates game
		void draw(); //Draws game
		void start_game(std::string mappath, std::string tilesetdir, std::string tileset, std::string chrtsetdir, std::string chrtset); //Starts game
		void end_game(); //Ends game
	//Map
		void draw_map(float posx, float posy); //Draws the map
	//Characters
		void draw_characters(float posx, float posy); //Draws characters
		
	//Camera
		void position_camera(float posx, float posy) { camera.set_point(posx,posy); } //Sets camera position
	//Input
		void link_mouse(mouse *nCursor) { cursor = nCursor; } //Sets mouse handle
		void link_keyboard(keyboard *nKeys) { keys = nKeys; } //Sets keyboard handle
private:
	//Data
		//System
			bool game_started; //Has the game started?
		//Level
			bool playerturn; //Is it the player's turn
		//Map
			map battlefield; //Battlefield matrix
			std::vector<tile*> terrain; //Tile array
			std::vector<texture*> terraintex; //Tile texture array
		//Characters
			std::vector<character*> army; //Character array
			std::vector<animation*> armytex; //Character animation array
		//Save

		//Camera
			point camera; //Origin of map
		//Input
			mouse *cursor; //Handle to mouse object
			keyboard *keys; //Handle to keyboard object
			texture cursor_tex; //Mouse representation
		//Game display
			//Windows
				texture main_window_tex;
				texture secondary_window_tex;
			//Selector
				point selector_pos;
				animation selector_tex;
};

//Constructor
game::game():
//System
	game_started(false),
//Level
	playerturn(true),
//Characters
	
//Input
	cursor(0),
	keys(0)
{
	
}

//Destructor
game::~game()
{
	end_game(); //End game if active
}

//Start game
void game::start_game(std::string mappath, std::string tilesetdir, std::string tileset, std::string chrtsetdir, std::string chrtset)
{
	//Check that game has not started
	if(game_started == false)
	{
		//Load battlefield
		battlefield.load_map(mappath);

		//Make objects for file loading
		std::ifstream file;
		std::string line, line2;

		//Load terrain
		file.open(tilesetdir + tileset); //Open tileset for reading
			while(file.good() == true)
			{
				std::getline(file,line); //Get tile properties path
				terrain.insert(terrain.end(),new tile(tilesetdir + line)); //Load tile properties
				std::getline(file,line); //Get tile texture path
				terraintex.insert(terraintex.end(),new texture(tilesetdir + line)); //Load tile texture
			}
		file.close(); //Close file

		//Load army
		file.open(chrtsetdir + chrtset); //Open character set for reading
			std::getline(file,line); //Get animation set path
			while(file.good() == true)
			{
				std::getline(file,line);
				army.insert(army.end(),new character(chrtsetdir + line)); //Load character
			}
		file.close(); //Close file

		//Load character animations
		armytex.insert(armytex.end(), new animation);
		armytex.at(0)->load_frame("Levels/Characters/Matrix/Warrior/WarriorStatic1.png",7);
		armytex.at(0)->load_frame("Levels/Characters/Matrix/Warrior/WarriorStatic2.png",7);
		armytex.at(0)->load_frame("Levels/Characters/Matrix/Warrior/WarriorStatic3.png",7);

		//Register game start
		game_started = true;
	}
}

//End game
void game::end_game()
{
	//Check that game has started
	if(game_started == true)
	{
		//Clear terrain properties
		for(unsigned int count = 0; count < terrain.size(); count++)
		{
			delete terrain.at(count);
			terrain.at(count) = 0;
		}
		terrain.clear();

		//Clear terrain textures
		for(unsigned int count = 0; count < terraintex.size(); count++)
		{
			delete terraintex.at(count);
			terraintex.at(count) = 0;
		}
		terraintex.clear();

		//Clear character textures
		for(unsigned int count = 0; count < armytex.size(); count++)
		{
			delete armytex.at(count);
			armytex.at(count) = 0;
		}
		armytex.clear();

		//Clear characters
		for(unsigned int count = 0; count < army.size(); count++)
		{
			delete army.at(count);
			army.at(count) = 0;
		}
		army.clear();

		//Register game end
		game_started = false;
	}
}

//Setup
void game::setup()
{
	cursor_tex.load_texture("Images/MOUSE.png"); //Load mouse icon

	selector_tex.load_frame("Images/SELECTOR_1.png",5); //Load selector
	selector_tex.load_frame("Images/SELECTOR_2.png",5);
	selector_tex.load_frame("Images/SELECTOR_3.png",5);
	selector_tex.load_frame("Images/SELECTOR_2.png",5);
}

//Update
void game::update()
{
	//Check that game has started
	if(game_started == true)
	{
		//Check that mouse is on MAIN_WINDOW
		if(RectHit(cursor->position.x, cursor->position.y, 0, 0, MAIN_WINDOW.left, MAIN_WINDOW.top, MAIN_WINDOW.right, MAIN_WINDOW.bottom) == true)
		{
			//Update selector
			selector_pos.x = cursor->position.x - ((int)cursor->position.x % (int)TILE_SIZE);
			selector_pos.y = cursor->position.y - ((int)cursor->position.y % (int)TILE_SIZE);
		}

		//Update animations
		selector_tex.update();

		for(unsigned int count = 0; count < armytex.size(); count++) //Characters
		{
			armytex.at(count)->update();
		}
	}
}

//Draw
void game::draw()
{
	//Check that game has started
	if(game_started == true)
	{
		//Draw windows
		DrawRect(MAIN_WINDOW.left,MAIN_WINDOW.top,MAIN_WINDOW.right,MAIN_WINDOW.bottom,MAIN_WINDOW_FILL); //Fill (Main)
		DrawRect(SECONDARY_WINDOW.left,SECONDARY_WINDOW.top,SECONDARY_WINDOW.right,SECONDARY_WINDOW.bottom,SECONDARY_WINDOW_FILL); //Fill (2nd)
		PencilRect(SECONDARY_WINDOW.left,SECONDARY_WINDOW.top,SECONDARY_WINDOW.right,SECONDARY_WINDOW.bottom,SECONDARY_WINDOW_BORDER_SIZE,SECONDARY_WINDOW_BORDER); //Border (2nd)

		//Draw battlefield
		draw_map(camera.x,camera.y); //Map

		//Draw characters
		draw_characters(camera.x,camera.y);

		//Draw others
		selector_tex.draw(selector_pos.x,selector_pos.y,TILE_SIZE,TILE_SIZE); //Selector
		cursor_tex.draw_texture(cursor->position.x,cursor->position.y); //Draw mouse
	}
}

//Draw map
void game::draw_map(float posx, float posy)
{
	//Check that game has started
	if(game_started == true)
	{
		//Draw tiles
		for(int x = 0; x < battlefield.get_width(); x++)
		{
			for(int y = 0; y < battlefield.get_height(); y++)
			{
				if((unsigned)battlefield.get_map(x,y) < terrain.size() && battlefield.get_map(x,y) >= 0) //Check that texture to be drawn exists
					terraintex.at(battlefield.get_map(x,y))->draw_texture(x*TILE_SIZE+posx,y*TILE_SIZE+posy,TILE_SIZE,TILE_SIZE);
				else
					std::cout << "Warning: Tile texture does not exist!\n";
			}
		}
	}
}

//Draw characters
void game::draw_characters(float posx, float posy)
{
	for(unsigned int count = 0; count < army.size(); count++)
	{
		armytex.at(0)->draw(army.at(count)->x * TILE_SIZE, army.at(count)->y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
	}
}
////////////////////////////

#endif