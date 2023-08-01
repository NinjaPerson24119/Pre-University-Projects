#include <Windows.h>
#include <windowsx.h>

#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

#pragma comment(lib,"glew32.lib")
#pragma comment(lib,"OpenGL32.lib")

#include <gl\glew.h>
#include <gl\GLU.h>
#include <gl\GL.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\projection.hpp>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam); //Window Proc Predeclaration

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path){

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open())
	{
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> VertexShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

	// Link the program
	fprintf(stdout, "Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage(std::max(InfoLogLength, int(1)));
	glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

//Globals
HWND hwnd = 0; //Window handle
HDC hdc = 0; //Device context handle
HGLRC hrc = 0; //Rendering context handle
int pixelformat; //Pixel format id

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Create, define, and register window class
	WNDCLASSEX wndclass; //Create
	ZeroMemory(&wndclass,sizeof(WNDCLASSEX)); //Clear
	wndclass.cbSize = sizeof(WNDCLASSEX); //Size
	wndclass.hCursor = LoadCursor(0,IDC_ARROW); //Mouse icon
	wndclass.lpfnWndProc = WindowProc; //Message handler
	wndclass.hInstance = hInstance; //Instance
	wndclass.hbrBackground = (HBRUSH)COLOR_WINDOW; //Background color
	wndclass.style = CS_HREDRAW | CS_VREDRAW; //Redraw on move or resize
	wndclass.lpszClassName = L"wndclass"; //Class name
	RegisterClassEx(&wndclass); //Register

	//Calculate window client size
	RECT wndsize = { 0, 0, 640, 480 }; //Window size
	AdjustWindowRectEx(&wndsize, WS_OVERLAPPEDWINDOW, false, 0); //Adjust window size

	//Create and show window
	hwnd = CreateWindowEx(0, L"wndclass", L"SandBox", WS_OVERLAPPEDWINDOW, 0, 0, wndsize.right - wndsize.left, wndsize.bottom - wndsize.top, 0, 0, hInstance, 0); //Create window
	ShowWindow(hwnd,nCmdShow); //Show window

	//OPENGL SANDBOX SETUP

	//Set clear color
	glClearColor(0,0,1,0);

	//Generate VAO and set as current
	GLuint vertexarray = 0;
	glGenVertexArrays(1,&vertexarray);
	glBindVertexArray(vertexarray);

	//Load shaders
	GLuint shaderid = LoadShaders("VertexShader.vert", "FragmentShader.frag");

	//Get uniform "mvp" handle
	GLuint MatrixID = glGetUniformLocation(shaderid, "MVP");

	//Generate model view matrix
	glm::mat4 projection = glm::perspective(45.f, 4.f / 3.f, 0.1f, 100.f); //Projection
	glm::mat4 view = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); //View

	//Apply transformations to triangle
	glm::mat4 r = glm::rotate(glm::mat4(1.f),90.f,glm::vec3(1.f,0.f,0.f));
	glm::mat4 s = glm::scale(glm::mat4(1.f),glm::vec3(1.f,2.f,1.f));
	glm::mat4 t = glm::translate(glm::mat4(1.f),glm::vec3(0.f,0.f,0.5f));
	glm::mat4 model = t*s*r; //Model

	glm::mat4 MVP = projection*view*model; //Combine to make mvp

	//Generate VBO and set as current
	GLuint vertexbuffer = 0;
	glGenBuffers(1,&vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);

	//Define vertices
	GLfloat vertices[] =
	{
		-1.f, -1.f, 0.f,
		1.f, -1.f, 0.f,
		0.f, 1.f, 0.f,
	};

	//Fill VBO with vertex data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	//Windows message pump
	MSG msg; //Windows message
	while(true)
	{
		while(PeekMessage(&msg,0,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg); //Translate message
			DispatchMessage(&msg); //Send message to Window Proc
		}

		//Exit in case of WM_QUIT
		if(msg.message == WM_QUIT)
			break;

		//OPENGL SANDBOX LOOP

		//Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Use loaded shader
		glUseProgram(shaderid);

		//Send transformation to shader
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		//Set vertex attributes and draw from buffer
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);
		
		//Swap buffers
		SwapBuffers(hdc);
	}

	//OPENGL SANDBOX CLEANUP
	glDeleteBuffers(1,&vertexbuffer);
	glDeleteVertexArrays(1,&vertexarray);
	glDeleteProgram(shaderid);

	return msg.wParam; //End Program
}

//Window Proc
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//Handle messages
	switch(uMsg)
	{
	case WM_CREATE:
		//Create and define pixel format descriptor
		PIXELFORMATDESCRIPTOR pfd; //Create
		ZeroMemory(&pfd,sizeof(PIXELFORMATDESCRIPTOR)); //Clear
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR); //Size
		pfd.nVersion = 1; //Version
		pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW; //Enable OpenGL, double buffering, and drawing to the window
		pfd.iPixelType = PFD_TYPE_RGBA; //Pixel format
		pfd.cColorBits = 24; //Color bits (Non-Alpha)
		pfd.cAlphaBits = 8; //Alpha bits
		pfd.cDepthBits = 32; //Depth buffer
		pfd.iLayerType = PFD_MAIN_PLANE; //Main layer

		//Get device context
		hdc = GetDC(hWnd);
		if(hdc == 0)
			return -1;

		//Find pixel format
		pixelformat = ChoosePixelFormat(hdc, &pfd);
		if(pixelformat == 0)
			return -1;

		//Set pixel format
		if(SetPixelFormat(hdc, pixelformat, &pfd) == false)
			return -1;

		//Create OpenGL context
		hrc = wglCreateContext(hdc);
		if(hrc == 0)
			return -1;

		//Set rendering context
		if(wglMakeCurrent(hdc, hrc) == false)
			return -1;

		//Initialize glew
		if(glewInit() != GLEW_OK)
			return -1;

		return 0;
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd); //Destroy the window
		return 0;
		break;
	case WM_DESTROY:
		//Release OpenGL context 
		if(hrc != 0) 
			wglDeleteContext(hrc);

		//Release device context
		if(hdc != 0)
			ReleaseDC(hWnd, hdc);

		wglMakeCurrent(0, 0); //Reset rendering context
		PostQuitMessage(0); //Terminate process
		return 0;
		break;
	case WM_KEYUP:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hwnd);
		}
		return 0;
		break;
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam); //Handle unhandled messages
}