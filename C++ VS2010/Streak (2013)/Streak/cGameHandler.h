#ifndef GAME_HANDLER_H
#define GAME_HANDLER_H

ship const default_player(SCREEN_WIDTH/2, SCREEN_HEIGHT-75, color(0.f,1.f,0.f), GREEN);
controller const default_coms(1.f,1.f,13.f,5.f, HORIZONTAL, color(1.f,0.f,0.f), 0);

//////////////////////////////
//Game handler class
class game_handler
{
public:
	game_handler(); //Game handler
	~game_handler();
	void reset_game(bool get_harder);
	void start_round(); //System commands
	void end_round();
	void update();
	void draw();
	void draw_stars();
	void draw_waves();
	void move_friendly(float x, float y) { if(round_active == true) friendly->move(x,y); } //Outside input commands
	void fire_friendly() { if(round_active == true) friendly->fire(); }
	void flip_pause() { if(paused == false) paused = true; else paused = false; Sleep(250); }
	ship const get_friendly() { if(interval == false) if(round_active == true) return *friendly; } //Outside output commands
	bool get_active() { return round_active; }
	bool get_paused() { return paused; }
	bool get_interval() { return interval; }
private:
	bool paused;
	bool interval;
	float interval_time;
	bool round_active;
	int rounds_started;
	ship *friendly;
	controller *enemy;
	stars *background;
};

//Constructor
game_handler::game_handler():
round_active(false),
rounds_started(0),
paused(false)
{
	srand(time(0));
	reset_game(true);
}

//Destructor
game_handler::~game_handler()
{
	end_round();
}

//Sets up game for a new round
void game_handler::start_round()
{
	//Check that round is inactive
	if(round_active == false)
	{
		//Setup background
		if(background == 0) background = new stars(default_stars_color);

		//Randomize stars
		background->randomize();

		//Setup ships
		if(friendly == 0) friendly = new ship(default_player);
		if(enemy == 0) enemy = new controller(default_coms);

		//Set the hostile of enemy
		enemy->confirm_hostile(friendly);

		//Set enemy formation
		enemy->reset_formation(int_FORMATION(rand()%5+1));

		//Confirm that round is active
		round_active = true;
	}
}

//Ends game
void game_handler::end_round()
{
	//Check that round is active
	if(round_active == true)
	{
		//Clear stars
		if(background != 0)
		{
			delete background;
			background = 0;
		}

		//Clear ships
		if(friendly != 0)
		{
			delete friendly;
			friendly = 0;
		}
	
		if(enemy != 0)
		{
			delete enemy;
			enemy = 0;
		}
	
		//Confirm that round is inactive
		round_active = false;
	}
}

//Update game
void game_handler::update()
{
	//Enable game pausing
	if(paused == false)
	{
		//Check that round is active
		if(round_active == true)
		{
			//Update ships
			enemy->update();
			friendly->update();
		
			//Round management
			if(enemy->swarm_left() == 0)
				reset_game(true);
			if(friendly->get_lives() == 0 && friendly->get_health() <= 50)
				reset_game(false);
		}
	}

	//Interval related
	if(interval == true)
	{
		if(interval_time > 0)
		{
			interval_time--;
			if(interval_time == 0)
			{
				interval = false;
				if(paused == true) flip_pause();
			}
		}
	}
}

//Draw stars
void game_handler::draw_stars()
{
	if(round_active == true)
		background->draw();
}

//Draw game
void game_handler::draw()
{
	//Check that round is active
	if(round_active == true)
	{
		enemy->draw();
		friendly->draw();
	}
}

//Reset game
void game_handler::reset_game(bool get_harder)
{
	end_round();
	start_round();
	if(get_harder == true) rounds_started++; //Increment round
	enemy->difficulty = rounds_started*default_difficultycurve; //Set difficulty
	if(paused == false) flip_pause(); //Ready interval
	interval = true;
	interval_time = default_interval_time;
}

//Draw waves
void game_handler::draw_waves()
{
	float total_size = (default_spacing+default_ship_size)/2;
	float origin = SCREEN_WIDTH/2-total_size*rounds_started/2;
	//Singles
	for(int count1 = 0; count1 < rounds_started; count1++)
	{
		DrawBlock(origin+total_size*count1,SCREEN_HEIGHT/2,default_ship_size/2,default_wave);
	}
}
//////////////////////////////

#endif