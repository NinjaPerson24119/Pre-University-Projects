#ifndef SHIP_H
#define SHIP_H

///////////////////////////
//Ship class
class ship
{
public:
	ship(float x, float y, color iBrush, TEAM iTeam);
	void update();
	void draw();
	void draw_bloom();
	void fire();
	void laser_update();
	void laser_draw();
	void move(float x, float y);
	void damage(int health_loss) { if(powerup_cycles == 0 || current_powerup != IVCB) health = health-health_loss; }
	void LaserHit(ship &arget);
	void reset_vector() { vector = point(0,0); }
	float get_x() { return location.x; }
	float get_y() { return location.y; }
	float get_size() { return size; }
	color get_brush() { return brush; }
	int get_lives() { return lives; }
	int get_shots() { return shots; }
	float get_health() { return health; }
	int get_bloom() { return bloom; }
	point get_vector() { return vector; }
	std::list<point> lasers; //Holds lasers
	void add_powerup(float cycles) { powerup_cycles = powerup_cycles+cycles; } //Powerup related
	void add_life() { lives++; }
	void set_current_powerup(POWERUP_TYPE nCurrent) { if(nCurrent != current_powerup) powerup_cycles = 0; current_powerup = nCurrent; }
private:
	point location;
	point vector;
	float size;
	color brush;
	point origin; //Holds laser point of origin
	RECOIL_EFFECT recoil; //Holds state of recoil effect 
	TEAM team;
	float tick; //Time last round was fired
	int shots; //How rounds left before overheat
	int lives; //How many respawns
	int health;
	float bloom; //How much to bloom ship
	float powerup_cycles; //Powerup related
	POWERUP_TYPE current_powerup;
};

//Constructor
ship::ship(float x, float y, color iBrush, TEAM iTeam):
location(x,y),
brush(iBrush),
size(default_ship_size),
origin(location),
recoil(NONE),
team(iTeam),
shots(default_ship_shot),
health(default_ship_health),
bloom(0),
tick(0),
powerup_cycles(0),
current_powerup(IVCB)
{
	lasers.clear(); //Clear lasers
	if(team == GREEN) lives = default_ship_lives; else lives = 0; //Set life count
}

//Move
void ship::move(float x, float y)
{ 
	if(bloom == 0) 
		if(powerup_cycles > 0 && current_powerup == SPEED)
		{
			vector = vector + point(x*default_speed_multiplier,y*default_speed_multiplier); 
		}
		else
		{
			vector = vector + point(x,y); 
		}
		
}

//Update
void ship::update()
{
	//Respawning
	if(bloom == default_ship_maxbloom)
		if(health <= 50)
			if(lives > 0)
			{
				lives--;
				health = default_ship_health;
				shots = default_ship_shot;
				vector = point(0,0);
				powerup_cycles = default_ship_ivcb; //Apply respawn invincibility
				current_powerup = IVCB;
			}
	if(health <= 50) bloom++;
	if(health > 50) if(bloom > 0) bloom--;

	laser_update(); //Update lasers

	if(bloom == 0 && health > 50)
	{
		//Cool ship gun
		if(cycles/SCREEN_FPS > tick/SCREEN_FPS + default_laser_coolmod/SCREEN_FPS)
		{
			tick = cycles;
			shots++;
		}

		//Cycle powerups
		if(powerup_cycles > 0)
			powerup_cycles--;

		//Auto heal
		if(range(health,51,99)) health++;

		if(lives > default_ship_maxlives) lives = default_ship_maxlives; //Maxout lives
		if(shots > default_ship_shot) shots = default_ship_shot; //Maxout shots
		if(health > default_ship_health) health = default_ship_health; //Maxout health

		//Add recoil to ship
		if(recoil == RECOIL)
		{
			if(team == GREEN) //Check team
			if(location.y < origin.y + size/8) //Check that recoil range is not met
				location.y = location.y + default_ship_recoilspeed; //Move ship
			else
				recoil = RETURNING;
		
			if(team == RED)
			if(location.y > origin.y - size/8)
				location.y = location.y - default_ship_recoilspeed;
			else
				recoil = RETURNING;
		}

		//Remove recoil from ship
		if(recoil == RETURNING)
		{
			if(team == GREEN)
			if(location.y > origin.y - size/8)
				location.y = location.y - default_ship_recoilspeed;
			else
				recoil = NONE;
		
			if(team == RED)
			if(location.y < origin.y + size/8)
				location.y = location.y + default_ship_recoilspeed;
			else
				recoil = NONE;
		}

		//Move ship
		location = location + vector; //Add vector to location

		if(location.x < 0) { location.x = 0; vector.x = 0; }//Stop moving offmap
		if(location.x > SCREEN_WIDTH-get_size()) { location.x = (float)(SCREEN_WIDTH-get_size()); vector.x = 0; }
		if(location.y < 0) { location.y = 0; vector.y = 0; }//Stop moving offmap
		if(location.y > SCREEN_HEIGHT-get_size()) { location.y = (float)(SCREEN_HEIGHT-get_size()); vector.y = 0; }

		if(vector.x > 0) vector.x = vector.x - 0.2f; //Decelerate
		if(vector.x < 0) vector.x = vector.x + 0.2f;
		if(vector.y > 0) vector.y = vector.y - 0.2f;
		if(vector.y < 0) vector.y = vector.y + 0.2f;
	
		if((vector.x > 0) && (vector.x < default_round)) vector.x = 0; //Round vector to avoid nudging back and forth
		if((vector.x < 0) && (vector.x > 0-default_round)) vector.x = 0;
		if((vector.y > 0) && (vector.y < default_round)) vector.y = 0;
		if((vector.y < 0) && (vector.y > 0-default_round)) vector.y = 0;
	}
}

//Draw
void ship::draw()
{
	if(team == GREEN) laser_draw();
	if(health > default_ship_lowesthealth && bloom == 0) DrawBlock(get_x(), get_y(),get_size(),brush.fade(SCREEN_COLOR,default_ship_health-health));
	if(team == GREEN) if(bloom < SCREEN_WIDTH || bloom < SCREEN_HEIGHT) if(health <= default_ship_lowesthealth || bloom != 0) BloomBlock(get_x(), get_y(),get_size(),brush.fade(SCREEN_COLOR,(default_ship_health-health)+bloom),bloom);
	
	//Draw powerup outline
	switch(current_powerup)
	{
	case IVCB:
		if(bloom == 0 && powerup_cycles > 0) PencilBlock(get_x(),get_y(),get_size(),default_powerup_thick,brush.fade(default_ivcb_color,100-(100/(powerup_cycles/SCREEN_FPS))));
		break;
	case DUAL:
		if(bloom == 0 && powerup_cycles > 0) PencilBlock(get_x(),get_y(),get_size(),default_powerup_thick,brush.fade(default_dual_color,100-(100/(powerup_cycles/SCREEN_FPS))));
		break;
	case SPEED:
		if(bloom == 0 && powerup_cycles > 0) PencilBlock(get_x(),get_y(),get_size(),default_powerup_thick,brush.fade(default_speed_color,100-(100/(powerup_cycles/SCREEN_FPS))));
		break;
	case LIFE:
		if(bloom == 0 && powerup_cycles > 0) PencilBlock(get_x(),get_y(),get_size(),default_powerup_thick,brush.fade(default_life_color,100-(100/(powerup_cycles/SCREEN_FPS))));
		break;
	}
}

//Draw bloom (For red team)
void ship::draw_bloom()
{
	if(bloom < SCREEN_WIDTH || bloom < SCREEN_HEIGHT) if(health <= default_ship_lowesthealth || bloom != 0) BloomBlock(get_x(), get_y(),get_size(),brush.fade(SCREEN_COLOR,(default_ship_health-health)+bloom),bloom);
}

//Update lasers
void ship::laser_update()
{
	for(std::list<point>::iterator scroll = lasers.begin(); scroll != lasers.end(); scroll++)
	{
		if(team == GREEN) //Move lasers
			scroll->y = scroll->y - default_laser_speed;
		else
			scroll->y = scroll->y + default_laser_speed;
	
		//Delete lasers
		if(scroll->y < 0-default_ship_size/4) 
		{
			lasers.erase(scroll);
			break;
		}
		if(scroll->y > SCREEN_HEIGHT+default_ship_size/4) 
		{
			lasers.erase(scroll);
			break;
		}
	}
}

//Draw lasers
void ship::laser_draw()
{
	for(std::list<point>::iterator scroll = lasers.begin(); scroll != lasers.end(); scroll++)
	{
		DrawBlock(scroll->x,scroll->y,get_size()/4,get_brush().fade(color(1.f,1.f,0.f),25.f));
	}
}

//Fire
void ship::fire()
{
	if(bloom == 0)
	{
		if(health > default_ship_lowesthealth)
		{
			if(shots != 0) //Check that ship is not overheated
			{
				//Check that ship is not thrown back
				if(recoil == NONE)
				{
					//Recoil effect
					location.y = origin.y; //Lock y
					origin = location; //Store origin
					recoil = RECOIL; //Set to recoil
		
					//Fire laser
					if(powerup_cycles == 0 || current_powerup != DUAL) 
					{
						lasers.push_front(point(location.x+(get_size()/3+get_size()/16),location.y)); //Send laser
					}
					else
					{
						lasers.push_front(point(location.x+get_size()/4,location.y));
						lasers.push_front(point(location.x+get_size()-get_size()/4,location.y));
					}
					shots--; //Heat gun

					//Save fire cycle
					tick = cycles;
				}
			}
		}
	}
}

//Check if ship laser has hit another ship
void ship::LaserHit(ship &target)
{
	for(std::list<point>::iterator scroll = lasers.begin(); scroll != lasers.end(); scroll++)
	{
		if(target.get_health() > 50 && target.get_bloom() == 0)
		{
			//Check colission
			if(BlockHit(scroll->x, scroll->y, get_size()/4, target.get_x(), target.get_y(), target.get_size()) == true)
				target.damage(default_ship_damage);
		}
	}
}
///////////////////////////

#endif