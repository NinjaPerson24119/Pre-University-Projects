#ifndef PRIMITIVES
#define PRIMITIVES

#ifndef MATH
#define MATH
#include <math.h>
#endif

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
void DrawRect(float l, float t, float r, float b, color brush)
{
	glBegin(GL_QUADS);
		glColor4f(brush.red,brush.green,brush.blue,brush.alpha); //Set drawing color
		glVertex2f(l,t); //Draw vertices
		glVertex2f(l,b);
		glVertex2f(r,b);
		glVertex2f(r,t);
		glColor4f(1,1,1,1); //Reset color to white
	glEnd();
}

//Draws a circle
void DrawCircle(float x, float y, float radius, int pieces, color brush)
{
	glBegin(GL_TRIANGLE_STRIP);
		glColor4f(brush.red,brush.green,brush.blue,brush.alpha); //Set drawing color
		for(int count = 0; count <= pieces; count++)
		{
			float angle = (360/pieces)*DEG_TO_RAD*count;
			glVertex2f(cos(angle)*radius+x,sin(angle)*radius+y);
			glVertex2f(x,y);
		}
		glColor4f(1,1,1,1); //Reset color to white
	glEnd();
}

//Draws a triangle
void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, color brush)
{
	glBegin(GL_TRIANGLES);
		glColor4f(brush.red,brush.green,brush.blue,brush.alpha);
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
		glVertex2f(x3,y3);
	glEnd();
}

//Draws a block outline
void PencilRect(float x, float y, float size, float thick, color brush)
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

//Draws a circle outline
void PencilCircle(float x, float y, float radius, int pieces, float thickness, color brush)
{
	double segsize = ((360/pieces)*180/3.14);

	glBegin(GL_LINE_LOOP);
		glColor4f(brush.red,brush.green,brush.blue,brush.alpha);
		for(int thick = 0; thick <= thickness; thick++)
		{
			for(int count = 0; count <= pieces; count++)
			{
				float angle = (360/pieces)*DEG_TO_RAD*count;
				glVertex2f(cos(angle)*radius+x,sin(angle)*radius+y);
			}
			radius--;
		}
		glColor4f(1,1,1,1);
	glEnd();
}

//Draws a line
void PencilLine(float x1, float y1, float x2, float y2, color brush)
{
	glBegin(GL_LINES);
		glColor4f(brush.red,brush.green,brush.blue,brush.alpha);
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
	glEnd();
}

//Draws a triangle outline
void PencilTriangle(float x1, float y1, float x2, float y2, float x3, float y3, color brush)
{
	glBegin(GL_LINE_STRIP);
		glColor4f(brush.red,brush.green,brush.blue,brush.alpha);
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
		glVertex2f(x3,y3);
		glVertex2f(x1,y1);
	glEnd();
}

#endif