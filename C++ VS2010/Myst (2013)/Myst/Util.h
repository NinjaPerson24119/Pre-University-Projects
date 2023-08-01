//Stable (False)
//Input devices linked and working properly!
//Transparency working
//Tile set loading
//Map loading
//Character loading extremely messed up. Something about converting "animation" to "animation*" during initialization. Perhaps an error when assigning
//animation handles to characters. :|

#ifndef UTIL_H
#define UTIL_H

//OpenGL
#include "OpenGL.h"

//DevIL
#undef _UNICODE
#include <IL/il.h>
#include <IL/ilu.h>

#ifndef WINDOWS_H
#define WINDOWS_H
#include <Windows.h>
#endif

//Rescources
#include "Base\Base.h"
#include "Drawing\Drawing.h"
#include "Physics\Physics.h"
#include "Input\Input.h"

//Window data
char const NAME[] = "Myst";
int const SCREEN_WIDTH = 640;
int const SCREEN_HEIGHT = 480;
int const SCREEN_FPS = 30;
color const SCREEN_COLOR(0.f,0.f,0.f);

//Input
mouse MOUSE;
keyboard KEYBOARD;

//Game
#include "cMatrix.h"
#include "cMap.h"
#include "cTile.h"
#include "cCharacter.h"
#include "cGame.h"
game myst;

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
	myst.link_mouse(&MOUSE); //Link mouse to game
	myst.link_keyboard(&KEYBOARD); //Link keyboard to game
	myst.setup(); //Setup game
	myst.start_game("Levels/Maps/Matrix/Matrix.mtx","Levels/Tiles/Matrix/","Matrix.tileset","Levels/Characters/Matrix/","Matrix.chrtset"); //Start game
}

//Updates game
void Update()
{
	myst.update();
}

//Renders screen
void Render()
{
	glClear(GL_COLOR_BUFFER_BIT); //Clear buffer

	glMatrixMode(GL_MODELVIEW); //Set model view
	glLoadIdentity();

	myst.draw(); //Draw myst

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
