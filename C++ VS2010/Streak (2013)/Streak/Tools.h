#ifndef TOOLS_H
#define TOOLS_H

//Checks if a number is even or odd
enum EVEN_ODD { EVEN, ODD };
EVEN_ODD even_odd(int number)
{
	if(number/2 * 2 == number)
		return EVEN;
	else
		return ODD;
}

//Checks if a number is within a range
bool range(int num, int lowest, int highest)
{
	if(num >= lowest && num <= highest) 
		return true;
	else 
		return false;
}

//Block hit
bool BlockHit(float x1, float y1, float size1, float x2, float y2, float size2)
{
	bool x_inrange = false, y_inrange = false;
	if(range(x1,x2,x2+size2) == true) x_inrange = true; //Check if (1)x is in range of (2)x
	if(range(x1+size1,x2,x2+size2) == true) x_inrange = true;
	if(range(y1,y2,y2+size2) == true) y_inrange = true; //Check if (1)y is in range of (2)y
	if(range(y1+size1,y2,y2+size2) == true) y_inrange = true;

	if(x_inrange == true && y_inrange == true) return true; //Colission detected
	return false; //No colission detected
}

//Draws a block
void DrawBlock(float x, float y, float size, color brush)
{
	glBegin(GL_QUADS);
		glColor4f(brush.red,brush.green,brush.blue,brush.alpha); //Set drawing color
		glVertex2f(x,y); //Draw vertices
		glVertex2f(x,y+size);
		glVertex2f(x+size,y+size);
		glVertex2f(x+size,y);
	glEnd();
}

//Draws a rectangle
void DrawRect(float l, float t, float r, float b, color brush)
{
	glBegin(GL_QUADS);
		glColor4f(brush.red,brush.green,brush.blue,brush.alpha); //Set drawing color
		glVertex2f(l,t); //Draw vertices
		glVertex2f(l,b);
		glVertex2f(r,b);
		glVertex2f(r,t);
	glEnd();
}

//Draws a block outline
void PencilBlock(float x, float y, float size, float thick, color brush)
{
	DrawRect(x,y,x+thick,y+size,brush); //Sides
	DrawRect(x+size-thick,y,x+size,y+size,brush);
	DrawRect(x,y,x+size,y+thick,brush); //Lids
	DrawRect(x,y+size-thick,x+size,y+size,brush);
}

//Draws a rectangle outline
void PencilRect(float l, float t, float r, float b, float thick, color brush)
{
	DrawRect(l,t,l+thick,b,brush); //Sides
	DrawRect(r-thick,t,r,b,brush);
	DrawRect(l,t,r,t+thick,brush); //Lids
	DrawRect(l,b-thick,r,b,brush);
}

//Draws a block with to colors
enum DIRECTION { UP, DOWN, LEFT, RIGHT }; //Directional enum
void TrailBlock(float x, float y, float size, color brush1, color brush2, DIRECTION direction)
{
	glBegin(GL_QUADS);
		if(direction == UP || direction == LEFT) glColor4f(brush2.red,brush2.green,brush2.blue,brush2.alpha); else glColor4f(brush1.red,brush1.green,brush1.blue,brush1.alpha);
		glVertex2f(x,y);
		if(direction == DOWN || direction == LEFT) glColor4f(brush2.red,brush2.green,brush2.blue,brush2.alpha); else glColor4f(brush1.red,brush1.green,brush1.blue,brush1.alpha);
		glVertex2f(x,y+size);
		if(direction == DOWN || direction == RIGHT) glColor4f(brush2.red,brush2.green,brush2.blue,brush2.alpha); else glColor4f(brush1.red,brush1.green,brush1.blue,brush1.alpha);
		glVertex2f(x+size,y+size);
		if(direction == UP || direction == RIGHT) glColor4f(brush2.red,brush2.green,brush2.blue,brush2.alpha); else glColor4f(brush1.red,brush1.green,brush1.blue,brush1.alpha);
		glVertex2f(x+size,y);
	glEnd();
}

//Draws a bloomed block
void BloomBlock(float x, float y, float size, color brush, float distance)
{
	DrawBlock(x-distance,y-distance,size/2,brush);
	DrawBlock(x-distance,y+size/2+distance,size/2,brush);
	DrawBlock(x+size/2+distance,y+size/2+distance,size/2,brush);
	DrawBlock(x+size/2+distance,y-distance,size/2,brush);
}

#endif