#ifndef STARS_H
#define STARS_H

///////////////////////////////////////
//Stars class
class stars
{
public:
	stars(color iStarColor);
	void randomize();
	void draw();
private:
	color star_color; //Color to draw stars
	point locations[20]; //Positions of stars
};

//Constructor
stars::stars(color iStarColor):
star_color(iStarColor)
{
	randomize();
}

//Randomize star locations
void stars::randomize()
{
	for(int count = 0; count < 20; count++)
	{
		locations[count].set_point((float)(rand()%SCREEN_WIDTH), (float)(rand()%SCREEN_HEIGHT));
	}
}

//Draw stars
void stars::draw()
{
	glBegin(GL_POINTS);
	glColor4f(star_color.red, star_color.green, star_color.blue, star_color.alpha);
	for(int count = 0; count < 20; count++)
	{
		glVertex2f((float)locations[count].x,(float)locations[count].y);
	}
	glEnd();
}
///////////////////////////////////////

#endif