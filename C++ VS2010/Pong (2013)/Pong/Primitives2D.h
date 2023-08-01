#ifndef PRIMITIVES2D
#define PRIMITIVES2D

#ifndef MATH
#define MATH
#include <math.h>
#endif

//Draws a point
void DrawPoint(float x, float y, color brush)
{
	glBegin(GL_POINTS);
		glColor4f(brush.red,brush.green,brush.blue,brush.alpha);
		glVertex2f(x,y);
		glColor4f(1,1,1,1);
	glEnd();
}

//Draw a line
void DrawLine(float x1, float y1, float x2, float y2, color brush)
{
	glBegin(GL_LINES);
		glColor4f(brush.red,brush.green,brush.blue,brush.alpha);
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
		glColor4f(1,1,1,1);
	glEnd();
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
		glColor4f(1,1,1,1); //Reset color to white
	glEnd();
}

//Draws a rectangle
void DrawRect(float x, float y, float width, float height, color brush)
{
	glBegin(GL_QUADS);
		glColor4f(brush.red,brush.green,brush.blue,brush.alpha); //Set drawing color
		glVertex2f(x,y); //Draw vertices
		glVertex2f(x,y+height);
		glVertex2f(x+width,y+height);
		glVertex2f(x+width,y);
		glColor4f(1,1,1,1); //Reset color to white
	glEnd();
}

//Draws a circle
void DrawCircle(float x, float y, float radius, int pieces, color brush, float percenttodraw = 1)
{
	glBegin(GL_TRIANGLE_STRIP);
		glColor4f(brush.red,brush.green,brush.blue,brush.alpha); //Set drawing color
		for(int count = 0; count <= pieces*percenttodraw; count++)
		{
			float angle = (360/pieces)*DEG_TO_RAD*count;
			glVertex2f(cos(angle)*radius+x,sin(angle)*radius+y);
			glVertex2f(x,y);
		}
		glColor4f(1,1,1,1); //Reset color to white
	glEnd();
}

//Draws a block outline
void PencilRect(float x, float y, float size, color brush)
{
	DrawLine(x,y,x+size,y,brush);
	DrawLine(x+size,y,x+size,y+size,brush);
	DrawLine(x+size,y+size,x,y+size,brush);
	DrawLine(x,y+size,x,y,brush);
}

//Draws a rectangle outline
void PencilRect(float x, float y, float width, float height, color brush)
{
	DrawLine(x,y,x+width,y,brush);
	DrawLine(x+width,y,x+width,y+height,brush);
	DrawLine(x+width,y+height,x,y+height,brush);
	DrawLine(x,y+height,x,y,brush);
}

#endif