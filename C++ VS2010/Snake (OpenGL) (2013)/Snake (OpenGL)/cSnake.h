//////////////////////////////////////
//Point class
class point
{
public:
	point(float iX, float iY);
	void set_point(float nX, float nY) { x = nX; y = nY; }
	float x,y;
};

//Constructor
point::point(float iX = 0.f, float iY = 0.f):
x(iX),
y(iY){}
//////////////////////////////////////

//////////////////////////////////////
//Color class
class color
{
public:
	color(float iRed, float iGreen, float iBlue);
	float red, green, blue;
};
//Constructor
color::color(float iRed, float iGreen, float iBlue):
red(iRed),
green(iGreen),
blue(iBlue) {}
//////////////////////////////////////

//////////////////////////////////////
//Snake class
class snake
{
public:
	snake(color iColor);
	void snake_operate();
	void reset_food();
	void draw_lose(int x, int y);
	point limbs[(SCREEN_WIDTH/BLOCKSIZE)*(SCREEN_WIDTH/BLOCKSIZE)];
	point vector;
	point food;
	int length;
	float spacing;
	color head, body, cfood;
};

//Constructor
snake::snake(color iColor):
length(3),
spacing(2.f),
vector(0.f,-1.f),
head(iColor),
body(iColor),
cfood(0.f,0.f,1.f)
{
	//Fade body color by 50%
	body.red = head.red/0.2f;
	body.green = head.green/0.2f;
	body.blue = head.blue/0.2f;

	for(int count = 0; count < length; count++) //Position initial limbs
	{
		limbs[count].set_point(SCREEN_WIDTH/BLOCKSIZE/2,SCREEN_HEIGHT/BLOCKSIZE/2+count);
	}

	reset_food(); //Setup food block
}

//Operate
void snake::snake_operate()
{
	//Test losing
	for(int count = 1; count < length; count++)
	{
		if((limbs[0].x == limbs[count].x) && (limbs[0].y == limbs[count].y)) LOSE = true;;
	}
	if((limbs[0].x == 0) || (limbs[0].x == SCREEN_WIDTH/BLOCKSIZE-1) || (limbs[0].y == 0) || (limbs[0].y == SCREEN_HEIGHT/BLOCKSIZE-1)) LOSE = true;
	if(LOSE == true) draw_lose(8,8);

	if((PAUSE == false) && (LOSE == false))
	{
		//Scrolling
		for(int count = 1; count < length; count++) //Start at 1 to avoid reading limbs[-1]
		{
			limbs[length-count] = limbs[length-count-1]; //Every snake limb becomes the limb in front of it
		}
		limbs[0].set_point(limbs[0].x+vector.x,limbs[0].y+vector.y); //Add vector to head location
	}

	//Draw vertices
	glBegin(GL_QUADS);
		
	if(LOSE == false)
	{
		for(int count = 0; count < length; count++)
		{
			if(count == 0) glColor3f(head.red,head.green,head.blue); else glColor3f(body.red,body.green,body.blue); //Set color
			glVertex2f(limbs[count].x*BLOCKSIZE+spacing,limbs[count].y*BLOCKSIZE+spacing);
			glVertex2f(limbs[count].x*BLOCKSIZE+spacing,limbs[count].y*BLOCKSIZE+BLOCKSIZE-spacing);
			glVertex2f(limbs[count].x*BLOCKSIZE+BLOCKSIZE-spacing,limbs[count].y*BLOCKSIZE+BLOCKSIZE-spacing);
			glVertex2f(limbs[count].x*BLOCKSIZE+BLOCKSIZE-spacing,limbs[count].y*BLOCKSIZE+spacing);
		}

		//Draw food block
		glColor3f(cfood.red,cfood.green,cfood.blue);
		glVertex2f(food.x*BLOCKSIZE+spacing,food.y*BLOCKSIZE+spacing);
		glVertex2f(food.x*BLOCKSIZE+spacing,food.y*BLOCKSIZE+BLOCKSIZE-spacing);
		glVertex2f(food.x*BLOCKSIZE+BLOCKSIZE-spacing,food.y*BLOCKSIZE+BLOCKSIZE-spacing);
		glVertex2f(food.x*BLOCKSIZE+BLOCKSIZE-spacing,food.y*BLOCKSIZE+spacing);
	}

	//Draw bordering
	for(int x = 0; x < SCREEN_WIDTH/BLOCKSIZE; x++)
	{
		for(int y = 0; y < SCREEN_HEIGHT/BLOCKSIZE; y++)
		{
			if((x == 0) || (x == SCREEN_WIDTH/BLOCKSIZE-1) || (y == 0) || (y == SCREEN_HEIGHT/BLOCKSIZE-1))
			{
				glColor3f(0.f,0.f,0.f);
				glVertex2f(x*BLOCKSIZE+spacing,y*BLOCKSIZE+spacing);
				glVertex2f(x*BLOCKSIZE+spacing,y*BLOCKSIZE+BLOCKSIZE-spacing);
				glVertex2f(x*BLOCKSIZE+BLOCKSIZE-spacing,y*BLOCKSIZE+BLOCKSIZE-spacing);
				glVertex2f(x*BLOCKSIZE+BLOCKSIZE-spacing,y*BLOCKSIZE+spacing);
			}
		}
	}

	glEnd();

	//Test grow
	if((limbs[0].x == food.x) && (limbs[0].y == food.y))
	{
		length++;
		reset_food();
	}
}

//Reset food
void snake::reset_food()
{
	//Get position
	bool repeat = false;
	do
	{
		repeat = false;
		food.x = rand()%(SCREEN_WIDTH/BLOCKSIZE);
		food.y = rand()%(SCREEN_HEIGHT/BLOCKSIZE);
		for(int count = 0; count < length; count++) //Test against spawning in snake
		{
			if((limbs[count].x == food.x) && (limbs[count].y == food.y)) repeat = true;
		}
		//Test against spawning in border
		if((food.x == 0) || (food.x == SCREEN_WIDTH/BLOCKSIZE-1) || (food.y == 0) || (food.y == SCREEN_HEIGHT/BLOCKSIZE-1)) repeat = true;
	} while(repeat);

	//Get color
	do
	{
		repeat = false;
		cfood.red = (float)rand()/(float)RAND_MAX;
		cfood.green = (float)rand()/(float)RAND_MAX;
		cfood.blue = (float)rand()/(float)RAND_MAX;
		if((cfood.red > 0.9f) && (cfood.green > 0.9f) && (cfood.blue > 0.9f)) repeat = true;
		if((cfood.red < 0.1f) && (cfood.green < 0.1f) && (cfood.blue < 0.1f)) repeat = true;
	} while(repeat);
}

//Draw LOSE
void snake::draw_lose(int x, int y)
{
	int cross[5][5] =
	{
		1,0,0,0,1,
		0,1,0,1,0,
		0,0,1,0,0,
		0,1,0,1,0,
		1,0,0,0,1,
	};

	glBegin(GL_QUADS);
		glColor3f(1.f,0.f,0.f); //Draw cross
		for(int scrollx = 0; scrollx <  5; scrollx++)
		{
			for(int scrolly = 0; scrolly < 5; scrolly++)
			{
				if(cross[scrollx][scrolly] == 1)
				{
					glVertex2f((x+scrollx)*BLOCKSIZE+spacing,(y+scrolly)*BLOCKSIZE+spacing);
					glVertex2f((x+scrollx)*BLOCKSIZE+spacing,(y+scrolly)*BLOCKSIZE+BLOCKSIZE-spacing);
					glVertex2f((x+scrollx)*BLOCKSIZE+BLOCKSIZE-spacing,(y+scrolly)*BLOCKSIZE+BLOCKSIZE-spacing);
					glVertex2f((x+scrollx)*BLOCKSIZE+BLOCKSIZE-spacing,(y+scrolly)*BLOCKSIZE+spacing);
				}
			}
		}
	glEnd();
}
//////////////////////////////////////