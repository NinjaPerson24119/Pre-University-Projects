#ifndef POWERUP_H
#define POWERUP_H

class ship; //Predefine ship

////////////////////////////////
//Powerup class
class powerup
{
public:
	powerup(float x, float y, POWERUP_TYPE iType, ship *iGoal, color iBrush);
	void update();
	void draw();
	void action();
	float get_x() { return location.x; }
	float get_y() { return location.y; }
	float get_size() { return size; }
	color get_brush() { return brush; }
	float get_bloom() { return bloom; }
	bool get_activated() { return activated; }
	void flip_activated() { activated = true; }
private:
	point location;
	point vector;
	float size;
	color brush;
	bool activated;
	float bloom;
	POWERUP_TYPE type;
	ship *goal;
};

//Constructor
powerup::powerup(float x, float y, POWERUP_TYPE iType, ship *iGoal, color iBrush):
location(x,y),
size(default_powerup_size),
brush(iBrush),
activated(false),
bloom(0),
type(iType),
goal(iGoal) {}

//Update
void powerup::update()
{
	if(goal != 0)
	{
		if(activated == false)
		{
			//Apply powerup to ship
			if(BlockHit(get_x(),get_y(),get_size(),goal->get_x(),goal->get_y(),goal->get_size()) == true)
			{
				activated = true;
				action();
			}
		}
	}

	//Move powerup
	if(activated == false)
	{
		vector.y = default_powerup_speed; //Set vector
		location = location + vector; //Apply falling motion
	}
	else
	{
		//Apply bloom
		bloom = bloom + default_powerup_bloom;
	}
}

//Draw
void powerup::draw()
{
	if(get_activated() == false)
	{
		DrawBlock(get_x(),get_y(),get_size(),get_brush()); //Draw solid block
		PencilBlock(get_x(),get_y(),get_size(),default_powerup_thick,get_brush().fade(SCREEN_COLOR,-25.f)); //Draw pencil block
	}
	else
	{
		BloomBlock(get_x(),get_y(),get_size(),brush.fade(SCREEN_COLOR,bloom),bloom); //Draw blooming powerup
	}
}

//Action
void powerup::action()
{
	switch(type)
	{
	case IVCB:
		goal->set_current_powerup(IVCB);
		goal->add_powerup(default_ivcb_cycles);
		break;
	case DUAL:
		goal->set_current_powerup(DUAL);
		goal->add_powerup(default_dual_cycles);
		break;
	case SPEED:
		goal->set_current_powerup(SPEED);
		goal->add_powerup(default_speed_cycles);
		break;
	case LIFE:
		goal->set_current_powerup(LIFE);
		goal->add_powerup(default_life_cycles);
		goal->add_life();
	}
}
////////////////////////////////

#endif