#ifndef UTIL_H
#define UTIL_H

#include "LOpenGL.h"
#include "cRectangle.h"
#include "cColor.h" //Color rescource
#include "cPoint.h" //Point rescource
#include "Tools.h"

//Window data
char const NAME[] = "Streak";
int const SCREEN_WIDTH = 400;
int const SCREEN_HEIGHT = 400;
int const BLOCK_SIZE = 20;
int const SCREEN_FPS = 30;
color const SCREEN_COLOR(0.f,0.f,0.f);
bool keys[4]; //Holds button states (z,x,c,v)
float cycles = 0; //How many frames have been drawn to date

//Game setup
#include "Defaults.h"
#include "cStars.h"
#include "cShip.h"
#include "cPowerup.h"
#include "cController.h"
#include "cGameHandler.h"

game_handler game; //Make game

//Draw hud (Game specific)
void DrawHud(ship player)
{
	DrawRect(0,SCREEN_HEIGHT - (SCREEN_HEIGHT/10), SCREEN_WIDTH, SCREEN_HEIGHT, color(0.3f,0.3f,0.3f)); //Draw HUD panel
	PencilRect(0,SCREEN_HEIGHT - (SCREEN_HEIGHT/10), SCREEN_WIDTH, SCREEN_HEIGHT, 4.f, color(0.15f,0.15f,0.15f)); //Draw HUD outline
	DrawRect(SCREEN_WIDTH/2-2, SCREEN_HEIGHT - (SCREEN_HEIGHT/10), SCREEN_WIDTH/2+2, SCREEN_HEIGHT, color(0.15f,0.15f,0.15f)); //Draw HUD center line
	for(int count = 0; count < player.get_lives(); count++) //Draw life indicator
	{
		DrawBlock(8 + (8*count) + (player.get_size()*count) ,SCREEN_HEIGHT-(SCREEN_HEIGHT/10) + 10, player.get_size(), player.get_brush());
	}
	for(int count = 0; count < player.get_shots(); count++) //Draw overheat indicator
	{
		DrawBlock(SCREEN_WIDTH/2+2 + (8*count+8) + (player.get_size()/4*count), SCREEN_HEIGHT-(SCREEN_HEIGHT/10)+18, player.get_size()/4, player.get_brush().fade(color(1.f,1.f,0.f),25.f));
	}
}

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
		printf("FAILED TO INITIALIZE OPENGL:\n", gluErrorString(error)); //Display error report
		return 1;
	}
	return true;
}

//Updates game
void Update()
{
	//Enable pausing
	if(keys[3] == true) game.flip_pause(); //Pause key
	if(game.get_paused() == false)
	{
		//Input operations
		if(keys[0] ==  true) game.move_friendly(-0.5f,0); //Move left
		if(keys[1] == true) game.move_friendly(0.5f,0); //Move right
		if(keys[2] == true) game.fire_friendly(); //Fire

		//Cycle
		if(cycles == 1000000000) cycles = 0;
		cycles++;
	}

	//Update game
	game.update();
}

//Renders screen
void Render()
{
	glClear(GL_COLOR_BUFFER_BIT); //Clear buffer

	glMatrixMode(GL_MODELVIEW); //Set model view
	glLoadIdentity();

	if(game.get_active() == true) game.draw_stars(); //Draw starry background
	if(game.get_interval() == true) game.draw_waves(); //Draw wave indicator
	if(game.get_interval() == false)
	{
		game.draw(); //Draw ships
		if(game.get_active() == true) DrawHud(game.get_friendly()); //Draw hud
	}

	glutSwapBuffers(); //Swap buffers
}

//Handles keyboard presses
void Keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'z':
		keys[0] = true;
		break;
	case 'x':
		keys[1] = true;
		break;
	case 'c':
		keys[2] = true;
		break;
	case 'v':
		keys[3] = true;
		break;
	}
}

//Handles keyboard releases
void KeyboardUp(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'z':
		keys[0] = false;
		break;
	case 'x':
		keys[1] = false;
		break;
	case 'c':
		keys[2] = false;
		break;
	case 'v':
		keys[3] = false;
		break;
	}
}

#endif
