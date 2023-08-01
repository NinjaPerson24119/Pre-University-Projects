#include <fstream>
#include <exception>
#include <Windows.h>
#include <windowsx.h>

#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "Custom/OpenGL/Shader.h"
#include "Custom/OpenGL/ShaderProgram.h"

LRESULT CALLBACK WindowProc(HWND Hwnd, UINT Msg, WPARAM Wparam, LPARAM Lparam);
void Draw();

std::fstream debuglog; //Debug log
HDC hdc; //Device context
HGLRC hrc; //Rendering context

//Window defaults
unsigned int WNDWIDTH = 800;
unsigned int WNDHEIGHT = 600;
LPCWSTR WNDNAME = L"OpenGL Demo";

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Debug log
	debuglog.open("debuglog.txt", std::fstream::out);

	if(!debuglog.is_open())
		return -1;
		
	//Window message
	MSG msg;

	try
	{
		//Describe window
		WNDCLASSEX wnd;
		memset(&wnd, 0, sizeof(wnd));
		wnd.cbSize = sizeof(wnd);
		wnd.hCursor = LoadCursor(0, IDC_ARROW);
		wnd.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wnd.lpfnWndProc = WindowProc;
		wnd.hInstance = hInstance;
		wnd.lpszClassName = L"Window";
		wnd.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;

		//Get ideal window size
		RECT wndclient = { 0, 0, WNDWIDTH, WNDHEIGHT };
		AdjustWindowRect(&wndclient, WS_OVERLAPPEDWINDOW, false);

		//Create and show window
		RegisterClassEx(&wnd);
		HWND hwnd = CreateWindowEx(0, L"Window", WNDNAME, WS_OVERLAPPEDWINDOW, 0, 0, wndclient.right - wndclient.left, wndclient.bottom - wndclient.top, 0, 0, hInstance, 0); 
		
		if(hwnd == 0)
			throw std::runtime_error("Main - Failed to create window!\n");

		ShowWindow(hwnd, nCmdShow);

		//**DEBUG**
		ctm::Shader vertshader("shader.vert");
		ctm::Shader fragshader("shader.frag");
		ctm::ShaderProgram shader(vertshader, fragshader);

		//Main loop
		while(true)
		{
			//Message pump
			while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
	
			if(msg.message == WM_QUIT)
				break;
	
			//Render
			Draw();
		}
	}
	catch(std::runtime_error Error)
	{
		debuglog << Error.what();
		return -1;
	}
	catch(std::bad_alloc Error)
	{
		debuglog << "Allocation failed!" << Error.what();
		return -1;
	}
	catch(...)
	{
		debuglog << "An unhandled error has occured!\n";
		return -1;
	}

	return msg.wParam;
}

//Window Procedure
LRESULT CALLBACK WindowProc(HWND Hwnd, UINT Msg, WPARAM Wparam, LPARAM Lparam)
{
	//Handle messages
	switch(Msg)
	{
	case WM_CREATE:
		static PIXELFORMATDESCRIPTOR pixelformat;
		static int pixelformatid;
		static GLenum error;

		//Get device context
		hdc = GetDC(Hwnd);

		//Describe pixels
		pixelformat = 
		{
			sizeof(pixelformat), //Size
			1, //Version
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //Flags
			PFD_TYPE_RGBA, //Pixel format
			24, //Pixel size excluding alpha
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			32, //Depth buffer size
			0, 0,
			PFD_MAIN_PLANE, //Layer
			0, 0, 0, 0
		};
		pixelformatid = ChoosePixelFormat(hdc, &pixelformat); //Get closest match

		//Validate pixel format
		if(pixelformatid == 0)
		{
			debuglog << "Main - Failed to find pixel format!\n";
			return -1;
		}

		//Set pixel format
		if(!SetPixelFormat(hdc, pixelformatid, &pixelformat))
		{
			debuglog << "Main - Failed to set pixel format!\n";
			return -1;
		}
	
		//Create OpenGL context
		hrc = wglCreateContext(hdc);

		if(hrc == 0)
		{
			debuglog << "Main - Failed to create OpenGL context!\n";
			return -1;
		}

		//Make context current
		if(!wglMakeCurrent(hdc, hrc))
		{
			debuglog << "Main - Failed to set OpenGL context as current!\n";
			return -1;
		}

		//Initialize GLEW
		if(glewInit() != GLEW_OK)
		{
			debuglog << "Main - Failed to initialize glew!\n";
			return -1;
		}

		//Check OpenGL version
		if(!GLEW_VERSION_3_3)
		{
			debuglog << "Main - OpenGL 3.3 is not supported!\n";
			return -1;
		}

		//Load identity matrix into projection and modelview
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Set orthographic projection
		glOrtho(0, WNDWIDTH, WNDHEIGHT, 0, 0, 1);

		//Set clear color
		glClearColor(0, 0, 0, 0);

		//Disable depth testing
		glDisable(GL_DEPTH_TEST);

		//Enable alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Check for errors in OpenGL
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			debuglog << "Main - OpenGL initialization has failed!" << glewGetErrorString(error) << "\n";
			return -1;
		}
		return 0;
	case WM_CLOSE:
		wglMakeCurrent(hdc, 0);
		wglDeleteContext(hrc);
		ReleaseDC(Hwnd, hdc);
		DestroyWindow(Hwnd);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	//Handle unhandled messages
	return DefWindowProc(Hwnd, Msg, Wparam, Lparam);
}

//Draw
void Draw()
{
	//Clear the off screen buffer
	glClear(GL_COLOR_BUFFER_BIT);

	//Swap buffers
	SwapBuffers(hdc);
}