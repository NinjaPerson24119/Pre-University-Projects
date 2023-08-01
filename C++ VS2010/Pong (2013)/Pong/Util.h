#ifndef UTIL_H
#define UTIL_H

const float PI = 3.1415926535897932384626433832795f;
const float DEG_TO_RAD = PI/180;
const float RAD_TO_DEG = 180/PI;

//OpenGL
#include "OpenGL.h"

//DevIL
#undef _UNICODE
#include <IL/il.h>
#include <IL/ilu.h>

//Rescources
#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

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
#include "cColor.h"
#include "cPoint.h"
#include "Extras.h"
#include "Colissions.h"
#include "Primitives2D.h"
#include "cTexture.h"
#include "cKeyboard.h"

//Window data
char const NAME[] = "Pong";
int const SCREEN_WIDTH = 640;
int const SCREEN_HEIGHT = 480;
int const SCREEN_FPS = 30;
color const SCREEN_COLOR(0.f,0.f,0.f);

//Input
keyboard KEYBOARD;

//Game
#include "cGame.h"
game pong;

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

//Setup
void Setup()
{
	srand((unsigned int)time(0)); //Seed randomizer
	pong.setup();
}

//Update
void Update()
{
	KEYBOARD.update();
	pong.update();
}

//Render
void Render()
{
	glClear(GL_COLOR_BUFFER_BIT); //Clear buffer

	glMatrixMode(GL_MODELVIEW); //Set model view
	glLoadIdentity();

	pong.draw();

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

#endif
