enum TEAM { FRIENDLY = 0, HOSTILE = 1 };
class ship; //Predefine ship

/////////////////////
//Weapon class
class weapon : public pObject
{
public:
	weapon(int initial_x, int initial_y, world *initial_home, unsigned char initial_icon); //Constructor
	//Get
	int get_temp() { return temp; }
	bool get_away() { return away; }
	//Actions
	void weapon_operate(TEAM faction, int reset_x, int reset_y);
	bool fire(TEAM faction);
	bool reload(int reset_x, int reset_y);
private:
	int temp; //How hot gun is
	int heatchange; //Change in heat when firing
	int maxheat; //Max heat for firing
	bool away; //Test if gun has fired
};

//Constructor
weapon::weapon(int initial_x, int initial_y, world *initial_home, unsigned char initial_icon) :
pObject(initial_x, initial_y, true, initial_icon, initial_home)
{
	temp = 0;
	heatchange = 1; //Heat increase 
	maxheat = 4; //Max heat (Max rounds = maxheat/heatchange)
	away = false;
}

//Fire
bool weapon::fire(TEAM faction)
{
	if(away == true) return false; //Check if projectile is available
	if(temp >= maxheat) return false; //Check for overheat

	temp = temp+heatchange; //Heat weapon
	hidden = false; //Show projectile
	away = true; //Send projectile
	d.locked  = true; //Lock vector (No deceleration)
	if(faction == FRIENDLY) { set_vector(0,-1); icon = 30; } //Send projectile on vector and set icon
	if(faction == HOSTILE) { set_vector(0,1); icon = 31; }

	return true;
}

//Reload
bool weapon::reload(int reset_x, int reset_y)
{
	if(away == false) return false; //Check if projectile is available to reload

	hidden = true; //Hide projectile
	away = false; //Ready projectile for firing
	set_position(reset_x,reset_y); //Reset projectile to ship
	d.locked = false; //Unlock vector (Deceleration)
	set_vector(0,0); //Kill projectile movement

	return true;
}

//Operate
void weapon::weapon_operate(TEAM faction, int reset_x, int reset_y)
{
	//Routine
	if(temp > 0) temp--; //Cool weapon
	update(); //Confirm and complete operations

	//Cleanup
	if(away == true)
	{
		if(y <= 0) reload(reset_x,reset_y); //Remove round once out of bounds
		if(y >= mSIZEX) reload(reset_x,reset_y);
	}
}

/////////////////////

/////////////////////
//Ship class
class ship : public pObject
{
public:
	ship(int initial_x, int initial_y, bool initial_hidden, unsigned char initial_icon, world *initial_home,TEAM initial_type);
	//Actions
	bool get_dead() { return dead; }
	void ship_operate();
	bool round_hit_ship(ship *b); //Collision bullet to ship
	//Data
	weapon gun; //Weapon
	TEAM type; //Fire direction(TEAM)
private:
	bool dead;
};

//Constructor
ship::ship(int initial_x, int initial_y, bool initial_hidden, unsigned char initial_icon, world *initial_home, TEAM initial_type) :
pObject(initial_x,initial_y,initial_hidden,initial_icon,initial_home),
gun(x,y,home,' ') //Icon left blank to be filled in later in constructor 
{
	type = initial_type;
	dead = false;
	if(type == FRIENDLY) gun.icon = 30; //Set gun icon now
	if(type == HOSTILE) gun.icon = 31;
}

//Round hit ship check
bool ship::round_hit_ship(ship *b)
{
	if( (gun.get_away() == true) && (b->get_dead() == false) ) //Check that round hit living target
		if( (gun.x == b->x ) && ( gun.y == b->y ) ) //Check that positions are same
		{
			gun.reload(x,y); //Reload gun 
			b->icon = '!'; //Display enemy as dead 
			return true;
		}
	return false; //No hit
}

//Operate
void ship::ship_operate()
{
	if(gun.get_away() == false) gun.set_position(x,y); //Reposition round to gun if not fired
	if(dead == true) hidden = true; else hidden = false; //Hide ship if destroyed
	if(dead != true) update(); //Operate ship
	if(icon == '!') dead = true; //Die if exploding
	gun.weapon_operate(type,x,y); //Operate gun
}

/////////////////////