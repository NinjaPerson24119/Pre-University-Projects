#include "GL_Includes.h"
#include <time.h>
#include <cstdlib>

//Window data
char const NAME[] = "Snake (OpenGL)";
int const SCREEN_WIDTH = 400;
int const SCREEN_HEIGHT = 400;
int const BLOCKSIZE = 20;
float const SCREEN_COLOR[4] = { 1.f, 1.f, 1.f, 1.f };
int const SCREEN_FPS = 10;
bool PAUSE = false;
bool LOSE = false;

//Snake setup
#include "cSnake.h"
snake player(color(0.f,1.f,0.f));

bool InitGL()
{
	glMatrixMode(GL_PROJECTION); //Set projection matrix
	glLoadIdentity();
	glOrtho(0.0,SCREEN_WIDTH,SCREEN_HEIGHT,0.0,1.0,-1.0); //Multiply matrix for screen coordinates

	glMatrixMode(GL_MODELVIEW); //Set modelview matrix
	glLoadIdentity();

	glClearColor(SCREEN_COLOR[0],SCREEN_COLOR[1],SCREEN_COLOR[2],SCREEN_COLOR[3]); //Set clear color

	GLenum error = glGetError(); //Get error report
	if(error != GL_NO_ERROR)
	{
		printf("FAILED TO INITIALIZE OPENGL:\n", gluErrorString(error)); //Display error report
		return 1;
	}
	return true;
}

void Update()
{

}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT); //Clear buffer

	glMatrixMode(GL_MODELVIEW); //Set model view
	glLoadIdentity();

	player.snake_operate();

	glutSwapBuffers(); //Swap buffers
}

void Keyboard(unsigned char key, int x, int y)
{
	if((LOSE == true) && (key != 0)) glutLeaveMainLoop(); //End game on keypress if lost
	switch(key)
	{
	case 'w': //Up
		if(PAUSE == false)
		if((player.vector.x != 0.f) && (player.vector.y != 1.f)) player.vector.set_point(0.f,-1.f);
		break;
	case 's': //Down
		if(PAUSE == false)
		if((player.vector.x != 0.f) && (player.vector.y != -1.f)) player.vector.set_point(0.f,1.f);
		break;
	case 'a': //Left
		if(PAUSE == false)
		if((player.vector.x != 1.f) && (player.vector.y != 0.f)) player.vector.set_point(-1.f,0.f);
		break;
	case 'd': //Right
		if(PAUSE == false)
		if((player.vector.x != -1.f) && (player.vector.y != 0.f)) player.vector.set_point(1.f,0.f);
		break;
	case 'q': //Pause
		switch(PAUSE)
		{
		case true:
			PAUSE = false;
			break;
		case false:
			PAUSE = true;
			break;
		}
		break;
	}
}