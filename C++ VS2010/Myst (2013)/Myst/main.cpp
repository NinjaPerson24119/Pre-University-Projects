#include "Util.h"

void RunMainLoop(int val)
{
	Update();
	Render();
	glutTimerFunc(1000/SCREEN_FPS,RunMainLoop,val); //Callback mainloop
}

int main(int argc, char *args[])
{
	glutInit(&argc,args); //Initalize glut
	glutInitContextVersion(2,1); //Set glut version
	glutInitDisplayMode(GLUT_DOUBLE); //Set double buffering
	glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT); //Set window size
	glutCreateWindow(NAME); //Show window

	if(InitGL() == false) //Check for initialization failure
	{
		printf("FAILED TO INITIALIZE OPENGL!\n");
	}
	glutKeyboardFunc(KeyboardFunc); //Set key handler
	glutKeyboardUpFunc(KeyboardUpFunc); //Set key release handler
	glutSetCursor(GLUT_CURSOR_NONE); //Set cursor to none
	glutPassiveMotionFunc(MouseMotion); //Set mouse motion handler (No buttons pressed)
	glutMotionFunc(MouseMotion); //Set mouse motion handler (Buttons pressed)
	glutMouseFunc(MouseClick); //Set mouse click handler
	glutDisplayFunc(Render); //Set display func

	Setup(); //Set up game

	glutTimerFunc(1000/SCREEN_FPS,RunMainLoop,0); //Set main loop
	glutMainLoop(); //Start main loop
}