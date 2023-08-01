//Map loading and drawing
//Displays loading and drawing
//Player drawing (Mostly)
//Player animating
//Colissions messed up //Adding check to see if block even applies to axis
//OOO  Moving on x... clearly blocks above and below should be ignored
//O|
//O|

#ifndef UTIL_H
#define UTIL_H

//OpenGL
#include "OpenGL.h"

//DevIL
#undef _UNICODE
#include <IL/il.h>
#include <IL/ilu.h>

//Rescources
#ifndef WINDOWS_H
#define WINDOWS_H
#include <Windows.h>
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef TIME_H
#define TIME_H
#include <time.h>
#endif

//Custom rescources
#include "CUSTOMLIB\Base\Base.h"
#include "CUSTOMLIB\Drawing\Drawing.h"
#include "CUSTOMLIB\Input\Input.h"
#include "CUSTOMLIB\Physics\Physics.h"

//Window data
char const NAME[] = "Life force";
int const SCREEN_WIDTH = 640;
int const SCREEN_HEIGHT = 480;
int const SCREEN_FPS = 30;
color const SCREEN_COLOR(0.f,0.f,0.f);

//Input
mouse MOUSE;
keyboard KEYBOARD;

//Game
#include "cSoldier.h"
#include "cGame.h"
game lifeforce;

//Initializes OpenGL
bool InitGL()
{
	glMatrixMode(GL_PROJECTION); //Set projection matrix
	glLoadIdentity();
	glOrtho(0.0,SCREEN_WIDTH,SCREEN_HEIGHT,0.0,1.0,-1.0); //Multiply matrix for screen coordinates

	glMatrixMode(GL_MODELVIEW); //Set modelview matrix
	glLoadIdentity();

	glClearColor(SCREEN_COLOR.red,SCREEN_COLOR.green,SCREEN_COLOR.blue,SCREEN_COLOR.alpha); //Set clear color

	glEnable(GL_BLEND); //Enable blending
	glDisable(GL_DEPTH_TEST); //Disable depth testing
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA); //Set blending parameters
	
	GLenum error = glGetError(); //Get error report
	if(error != GL_NO_ERROR)
	{
		std::cout << "Failed to initialize openGL! Error: " << gluErrorString(error) << "\n"; //Display error report
		return 1;
	}

	//Initialize devIL
	ilInit();
	iluInit();
	ilEnable(IL_ORIGIN_SET);
	ilClearColor(SCREEN_COLOR.red,SCREEN_COLOR.green,SCREEN_COLOR.blue,SCREEN_COLOR.alpha);
	ILenum ilerror = ilGetError(); //Get error report
	if(ilerror = IL_NO_ERROR)
	{
		std::cout << "Failed to initialize devIL! Error: " << iluErrorString(ilerror) << "\n";
		return false;
	}
	return true;
}

//Sets up game
void Setup()
{
	srand((unsigned int)time(0)); //Seed randomizer
	lifeforce.setup(); //Setup lifeforce
	lifeforce.start_round("Matrix.mtx"); //Start round
}

//Updates game
void Update()
{
	lifeforce.update();
}

//Renders screen
void Render()
{
	glClear(GL_COLOR_BUFFER_BIT); //Clear buffer

	glMatrixMode(GL_MODELVIEW); //Set model view
	glLoadIdentity();

	lifeforce.draw();

	glutSwapBuffers(); //Swap buffers
}

//Handles keyboard
void KeyboardFunc(unsigned char key, int x, int y)
{
	KEYBOARD.set_key(key,true);
}

//Handles keyboard buttons released
void KeyboardUpFunc(unsigned char key, int x, int y)
{
	KEYBOARD.set_key(key,false);
}

//Handles mouse motion
void MouseMotion(int x, int y)
{
	MOUSE.last_position = MOUSE.position; //Record last position
	MOUSE.position = point((float)x,(float)y);
}

//Handles mouse buttons
void MouseClick(int button, int state, int x, int y)
{
	MOUSE.flip_button(button);
}

#endif
