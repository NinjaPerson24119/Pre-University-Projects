#ifndef CONTROLLER_H
#define CONTROLLER_H

//Formation commands
FORMATION int_FORMATION(int num)
{
	switch(num)
	{
	case 1:
		return BLOCK;
		break;
	case 2:
		return CHECKER;
		break;
	case 3:
		return GRID;
		break;
	case 4:
		return HORIZONTAL;
		break;
	case 5:
		return VERTICAL;
		break;
	}
}

///////////////////////////////
//Controller class
class controller
{
public:
	controller(float x, float y, float ships_x, float ships_y, FORMATION formation, color brush, ship *iHostile);
	~controller();
	void draw();
	void update();
	void reset_formation(FORMATION formation);
	void move(float x, float y);
	int swarm_left();
	void confirm_hostile(ship *iHostile) { if(hostile == 0) if(iHostile != 0) hostile = iHostile; }
	int difficulty; //Modifier on shot chance
	powerup *POWERUP;
private:
	bool POWERUP_exist;
	std::list<ship> swarm; //Holds controlled ships
	ship *hostile; //Gives swarm and enemy access to each other
	rectangle size; //Represents size of swarm
	color swarm_color; //Color of all swarm ships
	DIRECTION direction; //What direction swarm is moving in
};

//Constructor
controller::controller(float x, float y, float ships_x, float ships_y, FORMATION formation, color brush, ship *iHostile):
hostile(iHostile),
direction(LEFT),
size(x,y,ships_x,ships_y),
swarm_color(brush),
difficulty(default_difficulty),
POWERUP_exist(false)
{
	POWERUP = 0;
	swarm.clear(); //Make sure lists are empty
	reset_formation(formation); //Set formation
}

//Destructor
controller::~controller()
{
	if(POWERUP_exist != false)
	{
		delete POWERUP;
		POWERUP = 0;
		POWERUP_exist = false;
	}
}

//Reset formation
void controller::reset_formation(FORMATION formation)
{
	if(swarm.empty() != true) swarm.clear(); //Make sure that swarm is empty
	for(int countx = 0; countx < size.right; countx++)
	{
		for(int county = 0; county < size.bottom; county++)
		{
			switch(formation) //Setup formation
			{
			case BLOCK:
				swarm.push_front(ship(size.left*default_ship_size+countx*(default_ship_size+default_spacing), size.top*default_ship_size+county*(default_ship_size+default_spacing),swarm_color,RED));
				break;
			case CHECKER:
				if(even_odd(countx) == ODD || even_odd(county) == ODD) swarm.push_front(ship(size.left*default_ship_size+countx*(default_ship_size+default_spacing), size.top*default_ship_size+county*(default_ship_size+default_spacing),swarm_color,RED));
				break;
			case GRID:
				if(even_odd(countx) == EVEN || even_odd(county) == ODD) swarm.push_front(ship(size.left*default_ship_size+countx*(default_ship_size+default_spacing), size.top*default_ship_size+county*(default_ship_size+default_spacing),swarm_color,RED));
				break;
			case VERTICAL:
				if(even_odd(countx) == EVEN) swarm.push_front(ship(size.left*default_ship_size+countx*(default_ship_size+default_spacing), size.top*default_ship_size+county*(default_ship_size+default_spacing),swarm_color,RED));
				break;
			case HORIZONTAL:
				if(even_odd(county) == EVEN) swarm.push_front(ship(size.left*default_ship_size+countx*(default_ship_size+default_spacing), size.top*default_ship_size+county*(default_ship_size+default_spacing),swarm_color,RED));
				break;
			}
		}
	}
}

//Draw
void controller::draw()
{
	for(std::list<ship>::iterator scroll = swarm.begin(); scroll != swarm.end(); scroll++)
	{
		if(scroll->get_bloom() > 0) scroll->draw_bloom(); //Draw bloomed ships
	}
	for(std::list<ship>::iterator scroll = swarm.begin(); scroll != swarm.end(); scroll++)
	{
		scroll->laser_draw(); //Draw lasers
	}
	for(std::list<ship>::iterator scroll = swarm.begin(); scroll != swarm.end(); scroll++)
	{
		if(scroll->get_bloom() == 0) scroll->draw(); //Draw ships
	}
	if(POWERUP_exist == true) POWERUP->draw();
}

//Update
void controller::update()
{
	//Data for com movement
	int lowest_x = 5000;
	int highest_x = 0;
	bool alive = true;
	bool drift = false;

	//Com movement (Preprocess)
	for(std::list<ship>::iterator scroll = swarm.begin(); scroll != swarm.end(); scroll++)
	{
		drift = false;
		if(scroll->get_vector().x < 0) if(scroll->get_x() < lowest_x) lowest_x = scroll->get_x(); //Return outside values of swarm
		if(scroll->get_vector().x > 0) if(scroll->get_x() > highest_x) highest_x = scroll->get_x();
		if(direction == LEFT) if(lowest_x+scroll->get_vector().x <= 0+default_spacing) drift = true; //Return drift
		if(direction == RIGHT) if(highest_x+scroll->get_vector().x >= SCREEN_WIDTH-default_spacing-default_ship_size) drift = true;
		if(drift == true) { scroll->reset_vector(); if(direction == LEFT) direction = RIGHT; else direction = LEFT; scroll->move(0,default_forward); } //Change direction
	}

	for(std::list<ship>::iterator scroll = swarm.begin(); scroll != swarm.end(); scroll++)
	{
		//Com movement (Actual)
		if(drift == false) if(direction == LEFT) if(scroll->get_vector().x > 0-default_com_speed) scroll->move(0-default_com_speed,0.f); //Move ship
		if(drift == false) if(direction == RIGHT) if(scroll->get_vector().x < default_com_speed) scroll->move(default_com_speed,0.f);

		//Save ship state (ALIVE or DEAD)
		if(scroll->get_health() > 50)
		{
			alive = true;
		}
		else
			alive = false;
	
		if(difficulty >= default_firechance-1) difficulty = default_firechance-1; //Maxout difficulty
		if(rand()%(default_firechance-difficulty) == 0) scroll->fire(); //Test for fire
		hostile->LaserHit(*scroll); //Test for colissions
		scroll->LaserHit(*hostile);
		scroll->update(); //Update ships

		//Handle powerup creation
		if(hostile->get_bloom() == 0 && hostile->get_health() > 50)
		{
			if((scroll->get_health() <= 50) && (alive == true))
			{
				switch(rand()%default_powerup_chance)
				{
				case 0: //IVCB
					if(POWERUP_exist == false) { POWERUP = new powerup(scroll->get_x(),scroll->get_y(),IVCB,hostile,default_ivcb_color); POWERUP_exist = true; }
					break;
				case 1: //DUAL
					if(POWERUP_exist == false) { POWERUP = new powerup(scroll->get_x(),scroll->get_y(),DUAL,hostile,default_dual_color); POWERUP_exist = true; }
					break;
				case 2: //SPEED
					if(POWERUP_exist == false) { POWERUP = new powerup(scroll->get_x(),scroll->get_y(),SPEED,hostile,default_speed_color); POWERUP_exist = true; }
					break;
				case 3: //LIFE
					if(POWERUP_exist == false) { POWERUP = new powerup(scroll->get_x(),scroll->get_y(),LIFE,hostile,default_life_color); POWERUP_exist = true; }
					break;
				}
			}
		}

		//Update powerups
		if(POWERUP_exist == true)
		{
			if((POWERUP->get_y() > SCREEN_HEIGHT) || (POWERUP->get_bloom() > SCREEN_WIDTH)) 
			{
				delete POWERUP;
				POWERUP = 0;
				POWERUP_exist = false;
			}
		}
		if(POWERUP_exist == true) POWERUP->update();
	}
}

//Move
void controller::move(float x, float y)
{
	for(std::list<ship>::iterator scroll = swarm.begin(); scroll != swarm.end(); scroll++)
	{
		scroll->move(x,y);
	}
}

//Swarm left
int controller::swarm_left()
{
	int temp = 0;
	for(std::list<ship>::iterator scroll = swarm.begin(); scroll != swarm.end(); scroll++)
	{
		if(scroll->get_health() > 50 && scroll->get_lives() == 0) temp++;
	}
	return temp;
}
///////////////////////////////

#endif