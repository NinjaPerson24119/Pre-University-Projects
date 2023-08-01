#ifndef SOLDIER_H
#define SOLDIER_H

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

//Representation defaults
color PRIMARY_ARMOR_COLOR(0,0,1);
color SECONDARY_ARMOR_COLOR(1,0,0);
color VISOR_COLOR(0.5f,0.5f,0.5f);
color LASER_COLOR(1,1,0);

rect HEAD(8,0,24,24);
rect VISOR(18,4,24,20);
rect NECK(12,16,20,28);
rect ARMS(14,36,32,42);
rect TORSO(12,28,20,48);
rect LEGS(13,48,19,64);

float LASERFADESPEED = 0.1f; //How fast lasers fade per cycle
float STRIDELENGTH = 32; //How long each stride is
float STRIDESPEED = 0.1f; //How much of the stride is moved per walk(1) (%)
point ARMROTATIONAXIS(16,39);
point LEGROTATIONAXIS(16,44);
point HARVESTERTRIGGERPOS(4,8);
point HARVESTERMUZZLEPOS(31,5);

//Movement defaults
float DECELERATION = 0.5f;
float MAXSPEEDX = 5.5f;
float MAXSPEEDY = 1.5f;

////////////////////
//Soldier class
class soldier
{
public:
	//System
		soldier(float x, float y);
		void draw(texture &harvester);
		void update();
		void walk(float howfar);
		void shoot(texture &harvester);
	//Data
		//Physics
			point position; 
			point lastposition;
			vector velocity;
			float stride; //Stride state (0-STRIDELENGTH) 
			bool strideending; //Is the stride ending	  
		//Stats
			float health; //Health %
			float lifeforce; //Lifeforce %
		//Armor
			float shield; //Shield integrity % 
			float shieldresist; //Shield resistance %
			float shieldrecharge; //Shield recharge per cycle %
		//Harvester (GENERAL)
			angle gunangle; //Direction gun is aimed
			std::vector<line> lasers; //Array of lasers
			std::vector<color> lasercolors; //Array of laser colors
			float guntemp; //How hot the harvester is
		//Harvester (COMBAT)
			float gunshotcost; //How much lifeforce each shot costs
			float gundamage; //How much damage each shot deals %
			float gunfirerate; //How many cycles between shots
		//Harvester (TERRAIN)
			float gunlfextract; //How much lifeforce is extracted from destroyed triangles
			float gunlfexpel; //How much lifeforce is expelled when building a triangle 
			float gungravraypow; //How powerful the gravity ray is (% of lifeforce extracted from target per cycle)
};

//Constructor
soldier::soldier(float x, float y):
//Physics
	position(x,y),
	stride(0),
	strideending(false),
//Stats
	health(1.f),
	lifeforce(1.f),
//Armor
	shield(1.f),
	shieldresist(0.f),
	shieldrecharge(0.01f),
//Harvester (GENERAL)
	guntemp(0),
//Harvester (COMBAT)
	gunshotcost(0.02f),
	gundamage(0.25),
	gunfirerate(0.5f*SCREEN_FPS),
//Harvester (TERRAIN)
	gunlfextract(5),
	gunlfexpel(10),
	gungravraypow(0.01f)
{}

//Draw
void soldier::draw(texture &harvester)
{
	//Lasers
	for(unsigned int count = 0; count < lasers.size(); count++)
	{
		PencilLine(lasers.at(count).x1,lasers.at(count).y1,lasers.at(count).x2,lasers.at(count).y2,lasercolors.at(count));
	}

	//Harvester
	glTranslatef(position.x+ARMS.left+cosf(gunangle.get_radians())*ARMS.get_width(),position.y+ARMS.top+sinf(gunangle.get_radians())*ARMS.get_width(),0);
	glRotatef(gunangle.get_degrees(),0,0,1);
	if(range(gunangle.get_degrees(),-90,90) == true)
		harvester.draw_texture(0-HARVESTERTRIGGERPOS.x,0-HARVESTERTRIGGERPOS.y,harvester.get_width(),harvester.get_height());
	else
		harvester.draw_texture(0-HARVESTERTRIGGERPOS.x,0-HARVESTERTRIGGERPOS.y+harvester.get_height()*0.5f,harvester.get_width(),-(signed)harvester.get_height());
	glLoadIdentity();

	//Arms
	glTranslatef(ARMROTATIONAXIS.x+position.x,ARMROTATIONAXIS.y+position.y,0);
	glRotatef(gunangle.get_degrees(),0,0,1);
	DrawRect(ARMS.left-ARMROTATIONAXIS.x,ARMS.top-ARMROTATIONAXIS.y,ARMS.get_width()-(ARMROTATIONAXIS.x-ARMS.left),ARMS.get_height()-(ARMROTATIONAXIS.y-ARMS.top),SECONDARY_ARMOR_COLOR);
	glLoadIdentity();

	DrawRect(NECK.left+position.x,NECK.top+position.y,NECK.right+position.x,NECK.bottom+position.y,SECONDARY_ARMOR_COLOR); //Neck
	DrawRect(HEAD.left+position.x,HEAD.top+position.y,HEAD.right+position.x,HEAD.bottom+position.y,PRIMARY_ARMOR_COLOR); //Head

	//Visor
	if(range(gunangle.get_degrees(),-90,90) == true)
		DrawRect(VISOR.left+position.x,VISOR.top+position.y,VISOR.right+position.x,VISOR.bottom+position.y,VISOR_COLOR);
	else
		DrawRect(HEAD.left+position.x,VISOR.top+position.y,HEAD.left+(VISOR.right-VISOR.left)+position.x,VISOR.bottom+position.y,VISOR_COLOR);

	//Legs (1)
	glTranslatef(LEGROTATIONAXIS.x+position.x,LEGROTATIONAXIS.y+position.y,0);
	glRotatef(0-((0-(-35))*stride/STRIDELENGTH),0,0,1);
	DrawRect(LEGS.left-LEGROTATIONAXIS.x,LEGS.top-LEGROTATIONAXIS.y,LEGS.get_width()-(LEGROTATIONAXIS.x-LEGS.left),LEGS.get_height()-(LEGROTATIONAXIS.y-LEGS.top),SECONDARY_ARMOR_COLOR);
	glLoadIdentity();

	//Legs (2)
	glTranslatef(LEGROTATIONAXIS.x+position.x,LEGROTATIONAXIS.y+position.y,0);
	glRotatef(0-((0-(35))*stride/STRIDELENGTH),0,0,1);
	DrawRect(LEGS.left-LEGROTATIONAXIS.x,LEGS.top-LEGROTATIONAXIS.y,LEGS.get_width()-(LEGROTATIONAXIS.x-LEGS.left),LEGS.get_height()-(LEGROTATIONAXIS.y-LEGS.top),SECONDARY_ARMOR_COLOR);
	glLoadIdentity();

	DrawRect(TORSO.left+position.x,TORSO.top+position.y,TORSO.right+position.x,TORSO.bottom+position.y,PRIMARY_ARMOR_COLOR); //Torso
}

//Update
void soldier::update()
{
	//Lock stats between 0 and 1
	if(health > 1) health = 1;
	if(health < 0) health = 0;
	if(shield > 1) shield = 1;
	if(shield < 0) shield = 0;
	if(lifeforce > 1) lifeforce = 1;
	if(lifeforce < 0) lifeforce = 0;

	if(shield > 0) health = 1; //Refill health when shield is up
	guntemp--; //Cool harvester
	if(guntemp < 0) guntemp = 0;

	//Delete and fade lasers
	for(unsigned int count = 0; count < lasercolors.size(); count++)
	{
		lasercolors.at(count).alpha -= LASERFADESPEED; //Fade
		/*
		if(lasercolors.back().alpha <= 0) //Delete
		{
			lasercolors.erase(lasercolors.end());
			if(count < lasers.size()) lasers.erase(lasers.end());
		}
		*/
	}

	//Move
	lastposition = position; //Record last position
	position = position + point(velocity.get_x(),velocity.get_y()); //Move position by vector
	velocity.decelerate(DECELERATION); //Decelerate vector
	if(velocity.get_x() > MAXSPEEDX) velocity.set_cartesian(MAXSPEEDX,velocity.get_y()); //Lock x at maxspeed (+)
	if(velocity.get_x() < -MAXSPEEDX) velocity.set_cartesian(-MAXSPEEDX,velocity.get_y()); //Lock x at maxspeed (-)
	if(velocity.get_y() > MAXSPEEDY) velocity.set_cartesian(velocity.get_x(),MAXSPEEDY); //Lock y at maxspeed (+)
	if(velocity.get_y() < -MAXSPEEDY) velocity.set_cartesian(velocity.get_x(),-MAXSPEEDY); //Lock y at maxspeed (-)
	if(velocity.get_y() == 0) walk(velocity.get_x()); //Set walking animation
}

//Walk
void soldier::walk(float howfar)
{
	if(strideending == false) stride = stride + STRIDESPEED*STRIDELENGTH*howfar; //Change stride
	if(strideending == true) stride = stride - STRIDESPEED*STRIDELENGTH*howfar;
	if(howfar > 0) //Change stride mode
	{
		if(stride <= 1) { strideending = false; stride = 0; } 
		if(stride >= STRIDELENGTH) { strideending = true; stride = STRIDELENGTH; }
	}
	else
	{
		if(stride <= 1) { strideending = true; stride = 0; } 
		if(stride >= STRIDELENGTH) { strideending = false; stride = STRIDELENGTH; }
	}
}

//Shoot
void soldier::shoot(texture &harvester)
{
	//Check that harvester is cooled
	if(guntemp <= 0)
	{
		//Calculate harvester muzzle position
		float hx = position.x+ARMS.left+cosf(gunangle.get_radians())*(ARMS.get_width()+(harvester.get_width()));
		float hy = position.y+ARMS.top+sinf(gunangle.get_radians())*(ARMS.get_width()+(harvester.get_height()));
	
		//Extend shot
		float lx = cosf(gunangle.get_radians())*(SCREEN_WIDTH+SCREEN_HEIGHT)+hx;
		float ly = sinf(gunangle.get_radians())*(SCREEN_WIDTH+SCREEN_HEIGHT)+hy;

		//Register shot
		lasers.insert(lasers.end(),line(hx,hy,lx,ly));
		lasercolors.insert(lasercolors.end(),LASER_COLOR);
	
		guntemp += gunfirerate; //Heat gun
		lifeforce -= gunshotcost; //Remove lifeforce
	}
}
////////////////////

#endif