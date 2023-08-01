#ifndef GAME_H
#define GAME_H

//Keyboard defaults
char DEFAULT_P1_UP = 'z';
char DEFAULT_P1_DOWN = 'x';
char DEFAULT_P1_TOGGLE = 'c';
char DEFAULT_P2_UP = 'n';
char DEFAULT_P2_DOWN = 'm';
char DEFAULT_P2_TOGGLE = 'b';

//Paddle defaults
float DEFAULT_PADDLE_WIDTH = 20;
float DEFAULT_PADDLE_HEIGHT = 60;
float DEFAULT_PADDLE_SPEED = 4;
float DEFAULT_COM_PADDLE_SPEED = 3.5f;
color DEFAULT_P1_PADDLE_COLOR = color(0,0,1);
color DEFAULT_P2_PADDLE_COLOR = color(1,0,0);
point DEFAULT_P1_PADDLE_POS = point(40,SCREEN_HEIGHT/2-DEFAULT_PADDLE_HEIGHT/2);
point DEFAULT_P2_PADDLE_POS = point(SCREEN_WIDTH-40-DEFAULT_PADDLE_WIDTH,SCREEN_HEIGHT/2-DEFAULT_PADDLE_HEIGHT/2);

//Ball defaults
int DEFAULT_BALL_PIECES = 90;
int DEFAULT_BALL_PATH_MOD = 0;
int DEFAULT_BALL_ANGLE_RANGE = 90;
float DEFAULT_BALL_SPEED = 5;
float DEFAULT_BALL_SPEED_BOOST = 0.f;
float DEFAULT_BALL_RADIUS = 6;
point DEFAULT_BALL_POS = point(SCREEN_WIDTH/2-DEFAULT_BALL_RADIUS,SCREEN_HEIGHT/2-DEFAULT_BALL_RADIUS);
color DEFAULT_BALL_COLOR = color(1,1,0);

//Icon defaults
point DEFAULT_P1_ICON_POS = point(20,SCREEN_HEIGHT-32-20);
point DEFAULT_P2_ICON_POS = point(SCREEN_WIDTH-32-20,SCREEN_HEIGHT-32-20);

//Tinted screen
float DEFAULT_TINT_SPEED = 0.1f;

//////////////////////////
//Game class
class game
{
public:
	//System
		game();
		~game();
		void startround();
		void endround();
		void setup();
		void update();
		void draw();
	//Ball
		void set_ballv(int angle);
private:
	//System
		bool roundstarted;
	//Paddles
		point p1, p2;
	//Ball
		point ballp, ballv;
		float ballspeed;
	//Textures
		texture controller, computer;
		bool p1com, p2com;
	//Tinted screen
		float tintpercent;
		bool tinting;
		color tintcolor;
};

//Constructor
game::game():
//System
	roundstarted(false),
//Paddles
	p1(DEFAULT_P1_PADDLE_POS),
	p2(DEFAULT_P2_PADDLE_POS),
//Ball
	ballp(DEFAULT_BALL_POS),
	ballspeed(DEFAULT_BALL_SPEED),
//Textures
	p1com(false),
	p2com(false),
//Tinted screen
	tintpercent(0),
	tinting(false),
	tintcolor(0,0,0)
{
	startround();	
}

//Destructor
game::~game()
{
	endround();
}

//Start round
void game::startround()
{
	//Check that round is not started
	if(roundstarted == false)
	{
		//Set initial ball vector
		int angle = rand()%360;
		set_ballv(angle);

		//Modify tint
		tinting = false;

		//Register round start
		roundstarted = true;
	}
}

//End round
void game::endround()
{
	//Check that round is started
	if(roundstarted == true)
	{
		//Reset paddle positions
		p1 = DEFAULT_P1_PADDLE_POS;
		p2 = DEFAULT_P2_PADDLE_POS;

		//Reset ball
		ballp = DEFAULT_BALL_POS;
		ballv = point(0,0);
		ballspeed = DEFAULT_BALL_SPEED;

		//Tint screen
		tinting = true;

		//Register round end
		roundstarted = false;
	}
}

//Setup
void game::setup()
{
	//Load textures
	controller.load_texture("controller.png");
	computer.load_texture("computer.png");
}

//Update
void game::update()
{
	//Modify tint screen
	if(tinting == false) tintpercent = tintpercent - DEFAULT_TINT_SPEED; //Modify percent
	if(tinting == true) tintpercent = tintpercent + DEFAULT_TINT_SPEED;
	if(tinting == false) if(tintpercent < 0) tintpercent = 0; //Apply percent boundaries
	if(tinting == true) if(tintpercent > 1) tintpercent = 1;
	if(tinting == true) if(tintpercent == 1) //End round when screen is fully tinted
	{
		endround();
	}

	//Automatically start round after tint disappears
	if(roundstarted == false && tintpercent == 1) startround();

	//Check that round is started
	if(roundstarted == true && tintpercent == 0)
	{
		//Update paddles
		if(p1com == false) //Move
		{
			if(KEYBOARD.get_key(DEFAULT_P1_UP) == true) p1.y = p1.y - DEFAULT_PADDLE_SPEED;
			if(KEYBOARD.get_key(DEFAULT_P1_DOWN) == true) p1.y = p1.y + DEFAULT_PADDLE_SPEED;
		}
		if(KEYBOARD.get_keytime(DEFAULT_P1_TOGGLE) == 1) //Mode toggle
			if(p1com == false)
				p1com = true;
			else
				p1com = false;
		
		if(p2com == false) //Move
		{
			if(KEYBOARD.get_key(DEFAULT_P2_UP) == true) p2.y = p2.y - DEFAULT_PADDLE_SPEED;
			if(KEYBOARD.get_key(DEFAULT_P2_DOWN) == true) p2.y = p2.y + DEFAULT_PADDLE_SPEED;
		}
		if(KEYBOARD.get_keytime(DEFAULT_P2_TOGGLE) == 1) //Mode toggle
			if(p2com == false)
				p2com = true;
			else
				p2com = false;

		//Update computer controlled paddles
		if(p1com == true)
		{
			if(ballv.x < 0)
			{
				if(ballp.y+ballv.y < p1.y+DEFAULT_PADDLE_HEIGHT/2) p1.y = p1.y - DEFAULT_COM_PADDLE_SPEED;
				if(ballp.y+ballv.y > p1.y+DEFAULT_PADDLE_HEIGHT/2) p1.y = p1.y + DEFAULT_COM_PADDLE_SPEED; 
			}
		}
		if(p2com == true)
		{
			if(ballv.x > 0)
			{
				if(ballp.y+ballv.y < p2.y+DEFAULT_PADDLE_HEIGHT/2) p2.y = p2.y - DEFAULT_COM_PADDLE_SPEED;
				if(ballp.y+ballv.y > p2.y+DEFAULT_PADDLE_HEIGHT/2) p2.y = p2.y + DEFAULT_COM_PADDLE_SPEED;
			}
		}

		//Update ball
		ballp = ballp + ballv; //Add vector

		//Block paddles at screen edges
		if(p1.y < 0) p1.y = 0;
		if(p1.y+DEFAULT_PADDLE_HEIGHT > SCREEN_HEIGHT) p1.y = SCREEN_HEIGHT-DEFAULT_PADDLE_HEIGHT;
		if(p2.y < 0) p2.y = 0;
		if(p2.y+DEFAULT_PADDLE_HEIGHT > SCREEN_HEIGHT) p2.y = SCREEN_HEIGHT-DEFAULT_PADDLE_HEIGHT;

		//Deflect ball
		if(ballp.y-DEFAULT_BALL_RADIUS < 0) //Up
		{
			ballp = ballp - ballv; //Revert to last position
			int angle = 0;
			if(ballv.x < 0) angle = (rand()%DEFAULT_BALL_ANGLE_RANGE)+90+DEFAULT_BALL_PATH_MOD;
			if(ballv.x > 0) angle = rand()%DEFAULT_BALL_ANGLE_RANGE+DEFAULT_BALL_PATH_MOD;
			set_ballv(angle);
		}
		if(ballp.y+DEFAULT_BALL_RADIUS > SCREEN_HEIGHT) //Down
		{
			ballp = ballp - ballv; //Revert to last position
			int angle = 0;
			if(ballv.x < 0) angle = (rand()%DEFAULT_BALL_ANGLE_RANGE)+180+DEFAULT_BALL_PATH_MOD;
			if(ballv.x > 0) angle = (rand()%DEFAULT_BALL_ANGLE_RANGE)+270+DEFAULT_BALL_PATH_MOD;
			set_ballv(angle);
		}
		if(ballp.x-DEFAULT_BALL_RADIUS < p1.x+DEFAULT_PADDLE_WIDTH) //Left
		{
			if(LineHit1D(ballp.y-ballv.y-DEFAULT_BALL_RADIUS,ballp.y-ballv.y+DEFAULT_BALL_RADIUS,p1.y,p1.y+DEFAULT_PADDLE_HEIGHT) == true)
			{
				ballp = ballp - ballv; //Revert to last position
				int angle = 0;
				if(ballv.y < 0) angle = (rand()%DEFAULT_BALL_ANGLE_RANGE)+270+DEFAULT_BALL_PATH_MOD;
				if(ballv.y > 0) angle = (rand()%DEFAULT_BALL_ANGLE_RANGE)+DEFAULT_BALL_PATH_MOD;
				ballspeed = ballspeed + DEFAULT_BALL_SPEED_BOOST;
				set_ballv(angle);
			}
		}
		if(ballp.x+DEFAULT_BALL_RADIUS > p2.x) //Right
		{
			if(LineHit1D(ballp.y-ballv.y-DEFAULT_BALL_RADIUS,ballp.y-ballv.y+DEFAULT_BALL_RADIUS,p2.y,p2.y+DEFAULT_PADDLE_HEIGHT) == true)
			{
				ballp = ballp - ballv; //Revert to last position
				int angle = (rand()%180)+90;
				if(ballv.y < 0) angle = (rand()%DEFAULT_BALL_ANGLE_RANGE)+180+DEFAULT_BALL_PATH_MOD;
				if(ballv.y > 0) angle = (rand()%DEFAULT_BALL_ANGLE_RANGE)+90+DEFAULT_BALL_PATH_MOD;
				ballspeed = ballspeed + DEFAULT_BALL_SPEED_BOOST;
				set_ballv(angle);
			}
		}

		//Check for scoring
		if(ballp.x-DEFAULT_BALL_RADIUS < p1.x+DEFAULT_PADDLE_WIDTH) 
		{
			tintcolor = DEFAULT_P2_PADDLE_COLOR;
			tinting = true;
		}
		if(ballp.x+DEFAULT_BALL_RADIUS > p2.x)
		{
			tintcolor = DEFAULT_P1_PADDLE_COLOR;
			tinting = true;
		}
	}
}

//Draw
void game::draw()
{
	//Check that round is started
	if(roundstarted == true)
	{
		//Draw paddles
		DrawRect(p1.x,p1.y,DEFAULT_PADDLE_WIDTH,DEFAULT_PADDLE_HEIGHT,DEFAULT_P1_PADDLE_COLOR);
		DrawRect(p2.x,p2.y,DEFAULT_PADDLE_WIDTH,DEFAULT_PADDLE_HEIGHT,DEFAULT_P2_PADDLE_COLOR);

		//Draw ball
		DrawCircle(ballp.x,ballp.y,DEFAULT_BALL_RADIUS,DEFAULT_BALL_PIECES,DEFAULT_BALL_COLOR);

		//Draw icons
		if(p1com == false) controller.draw_texture(DEFAULT_P1_ICON_POS.x,DEFAULT_P1_ICON_POS.y); else computer.draw_texture(DEFAULT_P1_ICON_POS.x,DEFAULT_P1_ICON_POS.y);
		if(p2com == false) controller.draw_texture(DEFAULT_P2_ICON_POS.x,DEFAULT_P2_ICON_POS.y); else computer.draw_texture(DEFAULT_P2_ICON_POS.x,DEFAULT_P2_ICON_POS.y);

		//Draw tint
		if(tintpercent != 0) DrawRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,color(0,0,0).fade(tintcolor,tintpercent));
	}
}

//Sets the ball vector by an angle
void game::set_ballv(int angle)
{
	ballv.x = cosf(angle*DEG_TO_RAD)*ballspeed;
	ballv.y = sinf(angle*DEG_TO_RAD)*ballspeed;
}
//////////////////////////

#endif