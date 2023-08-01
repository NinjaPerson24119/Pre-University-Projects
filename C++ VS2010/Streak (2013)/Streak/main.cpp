//Bloom directions are inverted

#include "Util.h"
#include "Custom/Memory/BlockAllocator.h"
#include "Custom/Memory/OverrideMemory.h"

void RunMainLoop(int val)
{
	Update();
	Render();
	glutTimerFunc(1000/SCREEN_FPS,RunMainLoop,val); //Callback mainloop
}

int main(int argc, char *args[])
{
	//Use custom allocator
	ctm::BlockAllocator alloc(new char[1000000], 100000, operator delete[]);
	ctm::SetMemoryAlignment(4);
	ctm::SetMemoryAllocator(&alloc);

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
	glutKeyboardUpFunc(KeyboardUp); //Set keyboard up handler
	glutDisplayFunc(Render); //Set display func
	glutTimerFunc(1000/SCREEN_FPS,RunMainLoop,0); //Set main loop
	glutMainLoop(); //Start main loop

	//Release memory
	alloc.Release();
}