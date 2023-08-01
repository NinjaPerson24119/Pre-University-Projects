#ifndef UTIL_H
#define UTIL_H

const float PI = 3.1415926535897932384626433832795f;
const float DEG_TO_RAD = PI/180;
const float RAD_TO_DEG = 180/PI;

//OpenGL
#include "OpenGL.h"

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
#include "cKeyboard.h"

//Window data
char const NAME[] = "Meteors";
int const SCREEN_WIDTH = 640;
int const SCREEN_HEIGHT = 480;
int const SCREEN_FPS = 30;
color const SCREEN_COLOR(0.f,0.f,0.f);

//Input
keyboard KEYBOARD;

//Game
#include "cStars.h"
#include "cMeteor.h"
#include "cGame.h"
game meteors;

//Initializes OpenGL
bool InitGL()
{
	glMatrixMode(GL_PROJECTION); //Set projection matrix
	glLoadIdentity();
	glOrtho(0.0,SCREEN_WIDTH,SCREEN_HEIGHT,0.0,1.0,-1.0); //Multiply matrix for screen coordinates

	glMatrixMode(GL_MODELVIEW); //Set modelview matrix
	glLoadIdentity();

	glClearColor(SCREEN_COLOR.red,SCREEN_COLOR.green,SCREEN_COLOR.blue,SCREEN_COLOR.alpha); //Set clear color
	
	GLenum error = glGetError(); //Get error report
	if(error != GL_NO_ERROR)
	{
		std::cout << "Failed to initialize openGL! Error: " << gluErrorString(error) << "\n"; //Display error report
		return 1;
	}
	return true;
}

//Setup
void Setup()
{
	srand((unsigned int)time(0)); //Seed randomizer
}

//Update
void Update()
{
	meteors.update();
}

//Render
void Render()
{
	glClear(GL_COLOR_BUFFER_BIT); //Clear buffer

	glMatrixMode(GL_MODELVIEW); //Set model view
	glLoadIdentity();

	meteors.draw();

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
