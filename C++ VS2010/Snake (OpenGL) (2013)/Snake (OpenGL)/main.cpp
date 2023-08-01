#include "GL_Utilities.h"

void RunMainLoop(int val)
{
	Update();
	Render();
	glutTimerFunc(1000/SCREEN_FPS,RunMainLoop,val); //Callback mainloop
}

int main(int argc, char *args[])
{
	//Seed randomizer
	srand(time(0));

	glutInit(&argc,args); //Initalize glut
	glutInitContextVersion(2,1); //Set glut version

	glutInitDisplayMode(GLUT_DOUBLE); //Set double buffering
	glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT); //Set window size
	glutCreateWindow(NAME); //Show window

	if(InitGL() == false) //Check for initialization failure
	{
		printf("FAILED TO INITIALIZE OPENGL!\n");
	}

	glutKeyboardFunc(Keyboard); //Set keyboard handler
	glutDisplayFunc(Render); //Set display func
	glutTimerFunc(1000/SCREEN_FPS,RunMainLoop,0); //Set main loop
	glutMainLoop(); //Start main loop
	return 0;
}