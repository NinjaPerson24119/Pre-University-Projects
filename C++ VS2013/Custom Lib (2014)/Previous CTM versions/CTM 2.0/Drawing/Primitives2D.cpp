#include "Primitives2D.h"
#include <math.h>

//Draws a point
void DrawPoint(FLOAT32 x, FLOAT32 y, color brush)
{
	glBegin(GL_POINTS);
		glColor4f(brush.red,brush.green,brush.blue,brush.alpha);
		glVertex2f(x,y);
		glColor4f(1,1,1,1);
	glEnd();
}

//Draw a line
void DrawLine(FLOAT32 x1, FLOAT32 y1, FLOAT32 x2, FLOAT32 y2, color brush)
{
	glBegin(GL_LINES);
		glColor4f(brush.red,brush.green,brush.blue,brush.alpha);
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
		glColor4f(1,1,1,1);
	glEnd();
}

//Draws a block
void DrawBlock(FLOAT32 x, FLOAT32 y, FLOAT32 size, color brush)
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
void DrawRect(FLOAT32 x, FLOAT32 y, FLOAT32 width, FLOAT32 height, color brush)
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
void DrawCircle(FLOAT32 x, FLOAT32 y, FLOAT32 radius, INT32 pieces, color brush, FLOAT32 percenttodraw)
{
	glBegin(GL_TRIANGLE_STRIP);
		glColor4f(brush.red,brush.green,brush.blue,brush.alpha); //Set drawing color
		for(INT32 count = 0; count <= pieces*percenttodraw; count++)
		{
			FLOAT32 angle = (360/pieces)*DEG_TO_RAD*count;
			glVertex2f(cos(angle)*radius+x,sin(angle)*radius+y);
			glVertex2f(x,y);
		}
		glColor4f(1,1,1,1); //Reset color to white
	glEnd();
}

//Draws a block outline
void PencilBlock(FLOAT32 x, FLOAT32 y, FLOAT32 size, color brush)
{
	DrawLine(x,y,x+size,y,brush);
	DrawLine(x+size,y,x+size,y+size,brush);
	DrawLine(x+size,y+size,x,y+size,brush);
	DrawLine(x,y+size,x,y,brush);
}

//Draws a rectangle outline
void PencilRect(FLOAT32 x, FLOAT32 y, FLOAT32 width, FLOAT32 height, color brush)
{
	DrawLine(x,y,x+width,y,brush);
	DrawLine(x+width,y,x+width,y+height,brush);
	DrawLine(x+width,y+height,x,y+height,brush);
	DrawLine(x,y+height,x,y,brush);
}