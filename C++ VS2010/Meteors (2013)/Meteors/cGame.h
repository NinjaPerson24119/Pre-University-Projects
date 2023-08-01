#ifndef GAME_H
#define GAME_H

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef MATH
#define MATH
#include <math.h>
#endif

//Keyboard defaults
char DEFAULT_UP = 'w';
char DEFAULT_DOWN = 's';
char DEFAULT_LEFT = 'a';
char DEFAULT_RIGHT = 'd';

//Shape defaults
int DEFAULT_CIRCLE_PIECES = 180;

//Backdrop defaults
int DEFAULT_STAR_COUNT = 20;
color DEFAULT_STAR_COLOR = color(1,1,1);

//Red screen defaults
float DEFAULT_RED_FADE_SPEED = 0.1f;

//Player defaults
float DEFAULT_PLAYER_SPEED = 5;
float DEFAULT_PLAYER_SIZE = 10;
color DEFAULT_PLAYER_COLOR = color(0,1,0);

//Meteor defaults
int DEFAULT_METEOR_COUNT = 10;
int DEFAULT_METEOR_DIF_RAMP = 30;
float DEFAULT_METEOR_SPEED = 3;
float DEFAULT_METEOR_SIZE = 20;
color DEFAULT_METEOR_COLOR = color(1,0,0);

//////////////////////////////////
//Game class
class game
{
public:
	//System
		game();
		void startround(); //Starts round
		void endround(); //Ends round
		void update(); //Update
		void draw(); //Draw
		bool get_roundstate() { return roundactive; }
	//Meteors
		void spawn_meteor();
private:
	//System
		bool roundactive; //Is round active?
	//Backdrop
		stars backdrop; //Starry backdrop
	//Red screen
		float redpercent; //Red screen fade percent
		bool redfadedirection;
	//Player
		point pos; //Player position
	//Meteors
		int maxmeteors;
		int diframp;
		std::vector<meteor> projectiles;
};

//Constructor
game::game():
//System
	roundactive(false),
//Backdrop
	backdrop(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,DEFAULT_STAR_COUNT,DEFAULT_STAR_COLOR),
//Red screen
	redpercent(0),
	redfadedirection(false),
//Player
	pos(SCREEN_WIDTH/2-DEFAULT_PLAYER_SIZE/2,SCREEN_HEIGHT/2-DEFAULT_PLAYER_SIZE/2),
//Meteors
	maxmeteors(DEFAULT_METEOR_COUNT),
	diframp(DEFAULT_METEOR_DIF_RAMP)
{
	startround();
	spawn_meteor();	
}
	
//Start round
void game::startround()
{
	if(roundactive == false)
	{
		//Randomize backdrop
		backdrop.randomize();

		//Modify red screen
		redfadedirection = false;

		//Register start of round
		roundactive = true;
	}
}

//End round
void game::endround()
{
	if(roundactive == true)
	{
		//Reset to default
		pos.x = SCREEN_WIDTH/2-DEFAULT_PLAYER_SIZE/2; //Reset X
		pos.y = SCREEN_HEIGHT/2-DEFAULT_PLAYER_SIZE/2; //Reset Y
		projectiles.clear(); //Clear meteors
		maxmeteors = DEFAULT_METEOR_COUNT; //Reset meteor count
		diframp = 0; //Reset difficulty ramp

		//Modify red screen
		redfadedirection = true;

		//Register end of round
		roundactive = false;
	}
}

//Update
void game::update()
{
	//Modify red screen 
	if(redfadedirection == false)
		if(redpercent > 0)
			redpercent -= DEFAULT_RED_FADE_SPEED;
	if(redpercent < 0) redpercent = 0;
	
	if(redfadedirection == true)
		if(redfadedirection == true)
			redpercent += DEFAULT_RED_FADE_SPEED;
	if(redpercent > 1) redpercent = 1;

	//Round handling
	if(roundactive == false)
		if(redpercent == 1)
			startround();

	//Check if round is active
	if(roundactive == true && redpercent == 0)
	{
		//Modify difficulty
		if(diframp > 0) diframp--;
		if(diframp == 0)
		{
			diframp = DEFAULT_METEOR_DIF_RAMP;
			maxmeteors++;
		}

		//Destroy meteors
		for(unsigned int count = 0; count < projectiles.size(); count++)
		{
			if(RectHit(projectiles.at(count).px,projectiles.at(count).py,DEFAULT_METEOR_SIZE,DEFAULT_METEOR_SIZE,0,0,(float)SCREEN_WIDTH,(float)SCREEN_HEIGHT) == false)
			{
				projectiles.erase(projectiles.begin()+count);
			}
		}

		//Spawn meteors
		while(projectiles.size() < (unsigned int)maxmeteors)
		{
			spawn_meteor();
		}

		//Move player
		if(KEYBOARD.get_key(DEFAULT_UP) == true) pos.y = pos.y - DEFAULT_PLAYER_SPEED;
		if(KEYBOARD.get_key(DEFAULT_DOWN) == true) pos.y = pos.y + DEFAULT_PLAYER_SPEED;
		if(KEYBOARD.get_key(DEFAULT_LEFT) == true) pos.x = pos.x - DEFAULT_PLAYER_SPEED;
		if(KEYBOARD.get_key(DEFAULT_RIGHT) == true) pos.x = pos.x + DEFAULT_PLAYER_SPEED;

		//Move meteors
		for(unsigned int count = 0; count < projectiles.size(); count++)
		{
			projectiles.at(count).px = projectiles.at(count).px + projectiles.at(count).vx;
			projectiles.at(count).py = projectiles.at(count).py + projectiles.at(count).vy;
		}

		//Block player at screen edges
		if(pos.y < 0) pos.y = 0;
		if(pos.y > SCREEN_HEIGHT-DEFAULT_PLAYER_SIZE) pos.y = SCREEN_HEIGHT-DEFAULT_PLAYER_SIZE;
		if(pos.x < 0) pos.x = 0;
		if(pos.x > SCREEN_WIDTH-DEFAULT_PLAYER_SIZE) pos.x = SCREEN_WIDTH-DEFAULT_PLAYER_SIZE;

		//Meteor colissions
		for(unsigned int count = 0; count < projectiles.size(); count++)
		{
			if(BlockHit(pos.x,pos.y,DEFAULT_PLAYER_SIZE,projectiles.at(count).px,projectiles.at(count).py,DEFAULT_METEOR_SIZE) == true)
				endround();
			//if(CircleHit(pos.x,pos.y,DEFAULT_PLAYER_SIZE,projectiles.at(count).px,projectiles.at(count).py,DEFAULT_METEOR_SIZE) == true)
				//endround();
		}
	}
}

//Draw
void game::draw()
{
	//Draw red screen
	if(redpercent != 0)
	{
		DrawRect(0,0,(float)SCREEN_WIDTH,(float)SCREEN_HEIGHT,color(redpercent,0,0));
	}
	
	//Check if round is active
	if(roundactive == true)
	{
		//Draw backdrop
		backdrop.draw();
	
		//Draw player
		DrawBlock(pos.x,pos.y,DEFAULT_PLAYER_SIZE,DEFAULT_PLAYER_COLOR);
		//DrawCircle(pos.x,pos.y,DEFAULT_PLAYER_SIZE,DEFAULT_CIRCLE_PIECES,DEFAULT_PLAYER_COLOR);

		//Draw meteors
		for(unsigned int count = 0; count < projectiles.size(); count++)
		{
			DrawBlock(projectiles.at(count).px,projectiles.at(count).py,DEFAULT_METEOR_SIZE,DEFAULT_METEOR_COLOR);
			//DrawCircle(projectiles.at(count).px,projectiles.at(count).py,DEFAULT_METEOR_SIZE,DEFAULT_CIRCLE_PIECES,DEFAULT_METEOR_COLOR);
		}
	}
}

//Spawn meteor
void game::spawn_meteor()
{
	float px = 0;
	float py = 0;
	
	//Randomize position
	int edge = rand()%4;
	switch(edge)
	{
	case 0:
		px = rand()%SCREEN_WIDTH;
		py = -DEFAULT_METEOR_SIZE;
		break;
	case 1:
		px = SCREEN_WIDTH;
		py = rand()%SCREEN_HEIGHT;
		break;
	case 2:
		px = rand()%SCREEN_WIDTH;
		py = SCREEN_HEIGHT;
		break;
	case 3:
		px = -DEFAULT_METEOR_SIZE;
		py = rand()%SCREEN_HEIGHT;
		break;
	}

	//Calculate angle
	float angle = atan2(pos.y-py,pos.x-px);

	//Calculate vector
	float vx = cosf(angle)*DEFAULT_METEOR_SPEED;
	float vy = sinf(angle)*DEFAULT_METEOR_SPEED;

	//Add meteor
	projectiles.insert(projectiles.end(),meteor(px,py,vx,vy));
}
//////////////////////////////////

#endif