#ifndef GAME_H
#define GAME_H

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef FSTREAM
#define FSTREAM
#include <fstream>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

//Generic defaults
const float BLOCKSIZE = 32;
const int CIRCLE_PIECES = 180;
const float CIRCLE_RADIUS = 32;

//Display defaults
point HEART_POSITION(32,SCREEN_HEIGHT-64);
color HEART_CIRCLE_COLOR(0.5f,0,0);
color SHIELD_CIRCLE_COLOR(0,0,0.5f);
point LIFEFORCE_POSITION(112,SCREEN_HEIGHT-64);
color LIFEFORCE_CIRCLE_COLOR(0.5f,0.5f,0);

//Physics defaults
float GRAVITY = 1.f;
float ACCELERATION = 1.f;
float JUMPACCELERATION = 20.f;

/////////////////////////
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
		void start_round(std::string filename); //Starts a new round
		void end_round(); //Ends current round
	//Functions
		void colissions(soldier &binded);
private:
	//Data
		//System
			bool roundstarted; //Has a round started?
		//Map
			std::vector<color> terrain; //Terrain colors
			map battlefield; //Level map
		//Soldiers
			soldier *player; //Player soldier
			std::vector<soldier*> enemies; //Array of enemy soldiers
			texture HARVESTER; //Harvester texture
		//Display
			texture HEART; //Heart texture
			texture LIFEFORCE; //Lifeforce texture
			texture SHIELD; //Shield texture
};

//Constructor
game::game():
//System
	roundstarted(false),
//Soldiers
	player(0)
{

}

//Destructor
game::~game()
{
	end_round();
}

//Start round
void game::start_round(std::string filename)
{
	if(roundstarted == false)
	{
		//Load battlefield
		battlefield.load_map(filename);

		//Build player
		for(int x = 0; x < battlefield.get_width(); x++) //Find player
		{
			for(int y = 0; y < battlefield.get_height(); y++)
			{
				if(battlefield.get_map(x,y) == 1)
				{
					battlefield.set_map(0,x,y); //Clear space on map for player
					if(y+1 < battlefield.get_height()) battlefield.set_map(0,x,y+1);
					player = new soldier(x*BLOCKSIZE,y*BLOCKSIZE); //Build player
				}
			}
		}

		//Build enemies
		for(int x = 0; x < battlefield.get_width(); x++)
		{
			for(int y = 0; y < battlefield.get_height(); y++)
			{
				if(battlefield.get_map(x,y) == 2)
				{
					battlefield.set_map(0,x,y); //Clear space on map for enemy
					if(y+1 < battlefield.get_height()) battlefield.set_map(0,x,y+1);
					enemies.insert(enemies.end(), new soldier(x*BLOCKSIZE,y*BLOCKSIZE));
				}
			}
		}

		roundstarted = true; //Register round start
	}
}

//End round
void game::end_round()
{
	if(roundstarted == true)
	{
		//Delete player
		if(player != 0)
		{
			delete player;
			player = 0;
		}

		//Delete enemies 
		for(unsigned int count = 0; count < enemies.size(); count++)
		{
			delete enemies.at(count);
			enemies.at(count) = 0;
		}
		enemies.clear();

		roundstarted = false; //Register round end
	}
}

//Setup
void game::setup()
{
	//Set terrain colors
	terrain.insert(terrain.end(),color(0.73f,0.48f,0.34f)); //Dirt
	terrain.insert(terrain.end(),color(0,1,0)); //Grass

	//Load textures
	HEART.load_texture("IMAGES/HEART.png");
	LIFEFORCE.load_texture("IMAGES/LIFEFORCE.png");
	SHIELD.load_texture("IMAGES/SHIELD.png");
	HARVESTER.load_texture("IMAGES/HARVESTER.png");
}

//Update
void game::update()
{
	//Check that round has started
	if(roundstarted == true)
	{
		//Controls
		if(KEYBOARD.get_key('a') == true) { player->velocity.add_cartesian(-ACCELERATION,0); } //Walk left
		if(KEYBOARD.get_key('d') == true) { player->velocity.add_cartesian(ACCELERATION,0); } //Walk right
		if((KEYBOARD.get_key('a') == false) && (KEYBOARD.get_key('d') == false)) if(player->strideending == true) if(player->stride > STRIDELENGTH/2) player->walk(1); //End walk cycle
		if(KEYBOARD.get_key('w') == true) if((int)player->velocity.get_y() == 0) player->velocity.add_cartesian(0,-1);
		if(MOUSE.get_button(0) == true) { player->shoot(HARVESTER); } //Shoot

		//Update player harvester based on mouse position
		player->gunangle.set_radians(atan2(MOUSE.position.y-(player->position.y+32), MOUSE.position.x-(player->position.x+32)));

		//Gravity
		//player->velocity.add_cartesian(0,GRAVITY);
		for(unsigned int count = 0; count < enemies.size(); count++)
		{
			//enemies.at(count)->velocity.add_cartesian(0,GRAVITY);
		}

		//Soldier colissions
		colissions(*player);
		for(unsigned int count = 0; count < enemies.size(); count++)
		{
			colissions(*enemies.at(count));
		}

		//Update soldiers
		player->update();
		for(unsigned int count = 0; count < enemies.size(); count++)
		{
			enemies.at(count)->gunangle.set_degrees(enemies.at(count)->gunangle.get_degrees()+1);
			enemies.at(count)->update();
			enemies.at(count)->walk(1);
		}
	}
}

//Draw
void game::draw()
{
	//Check that round has started
	if(roundstarted == true)
	{
		//Draw map
		for(int x = 0; x < battlefield.get_width(); x++)
		{
			for(int y = 0; y < battlefield.get_height(); y++)
			{
				if(battlefield.get_map(x,y)-3 > (signed)terrain.size()) //Make sure terrain type exists
				{
					std::cout << "Terrain type " << battlefield.get_map(x,y)-3 << " does not exist!\n";
					break;
				}
				if(battlefield.get_map(x,y) > 2) //0-2 are ignored (EMPTY,PLAYERHEAD,ENEMYHEAD)
				{
					DrawRect(x*BLOCKSIZE,y*BLOCKSIZE,x*BLOCKSIZE+BLOCKSIZE,y*BLOCKSIZE+BLOCKSIZE,terrain.at(battlefield.get_map(x,y)-3));
				}
			}
		}

		//Draw soldiers
		player->draw(HARVESTER);
		for(unsigned int count = 0; count < enemies.size(); count++)
		{
			enemies.at(count)->draw(HARVESTER);
			if(rand()%50 == 0) enemies.at(count)->shoot(HARVESTER);
		}

		//Draw displays
		DrawCircle(HEART_POSITION.x+CIRCLE_RADIUS/2,HEART_POSITION.y+CIRCLE_RADIUS/2,CIRCLE_RADIUS,CIRCLE_PIECES,HEART_CIRCLE_COLOR.fade(SCREEN_COLOR,0.25f)); //Main heart circle
		DrawCircle(HEART_POSITION.x+BLOCKSIZE/2,HEART_POSITION.y+BLOCKSIZE/2,CIRCLE_RADIUS,CIRCLE_PIECES,HEART_CIRCLE_COLOR.fade(SHIELD_CIRCLE_COLOR,player->shield),player->health); //Percent heart circle
		PencilCircle(HEART_POSITION.x+CIRCLE_RADIUS/2,HEART_POSITION.y+CIRCLE_RADIUS/2,CIRCLE_RADIUS,CIRCLE_PIECES,0,HEART_CIRCLE_COLOR.fade(SHIELD_CIRCLE_COLOR,player->shield).fade(SCREEN_COLOR,-1.f)); //Border heart circle
		if(player->shield != 0) SHIELD.draw_texture(HEART_POSITION.x,HEART_POSITION.y,BLOCKSIZE,BLOCKSIZE); else HEART.draw_texture(HEART_POSITION.x,HEART_POSITION.y,BLOCKSIZE,BLOCKSIZE); //Heart

		DrawCircle(LIFEFORCE_POSITION.x+CIRCLE_RADIUS/2,LIFEFORCE_POSITION.y+CIRCLE_RADIUS/2,CIRCLE_RADIUS,CIRCLE_PIECES,LIFEFORCE_CIRCLE_COLOR.fade(SCREEN_COLOR,0.25f)); //Main lifeforce circle
		DrawCircle(LIFEFORCE_POSITION.x+BLOCKSIZE/2,LIFEFORCE_POSITION.y+BLOCKSIZE/2,CIRCLE_RADIUS,CIRCLE_PIECES,LIFEFORCE_CIRCLE_COLOR,player->lifeforce); //Percent lifeforce circle
		PencilCircle(LIFEFORCE_POSITION.x+CIRCLE_RADIUS/2,LIFEFORCE_POSITION.y+CIRCLE_RADIUS/2,CIRCLE_RADIUS,CIRCLE_PIECES,0,LIFEFORCE_CIRCLE_COLOR.fade(SCREEN_COLOR,-1.f)); //Border lifeforce circle
		LIFEFORCE.draw_texture(LIFEFORCE_POSITION.x,LIFEFORCE_POSITION.y,BLOCKSIZE,BLOCKSIZE); //Lifeforce

		//Draw mouse
		DrawPoint(MOUSE.position.x,MOUSE.position.y,color(1,0,0));
	}
}

//Colissions
void game::colissions(soldier &binded)
{
	for(int x = 0; x < battlefield.get_width(); x++) //Scroll x
	{
		for(int y = 0; y < battlefield.get_height(); y++) //Scroll y
		{
			if(battlefield.get_map(x,y) != 0) //Check for solid
			{
				//Check for overall hit
				if(RectHit(binded.position.x+binded.velocity.get_x()+HEAD.left+1,binded.position.y+binded.velocity.get_y()+1,HEAD.get_width()-2,64-2,x*BLOCKSIZE,y*BLOCKSIZE,BLOCKSIZE,BLOCKSIZE) == true)
				{
					std::cout << "X: " << binded.velocity.get_x() << "\n";
					std::cout << "Y: " << binded.velocity.get_y() << "\n";
					//Check for precise hit and resolve (Check velocity -> Check edge -> Resolve)
					if(binded.position.x+binded.velocity.get_x()+HEAD.left < x*BLOCKSIZE+BLOCKSIZE) if(binded.velocity.get_x() < 0) binded.velocity.set_cartesian((x*BLOCKSIZE+BLOCKSIZE)-(binded.position.x+HEAD.left),binded.velocity.get_y()); //Left
					if(binded.position.x+binded.velocity.get_x()+HEAD.left+HEAD.get_width() > x*BLOCKSIZE) if(binded.velocity.get_x() > 0) binded.velocity.set_cartesian((x*BLOCKSIZE)-(binded.position.x+HEAD.left+HEAD.get_width()),binded.velocity.get_y()); //Right
					if(binded.position.y+binded.velocity.get_y() < y*BLOCKSIZE+BLOCKSIZE) if(binded.velocity.get_y() < 0) binded.velocity.set_cartesian(binded.velocity.get_x(),(y*BLOCKSIZE+BLOCKSIZE)-(binded.position.y)); //Up
				}
			}
		}
	}
}
/////////////////////////

#endif