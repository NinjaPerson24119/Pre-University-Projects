#include <Custom/Graphics/Window.h>
#include <Custom/External/OpenGL.h>
#include <assert.h>
#include <stdexcept>
#include <string>

namespace ctm
{

static Window *proxywindow = nullptr;
static unsigned int pixelsize = 32;
HGLRC Window::hrc = 0;
unsigned int Window::windowsmade = 0;
static std::mutex contextlock;

PIXELFORMATDESCRIPTOR Window::RGBA32 =
{
	sizeof(RGBA32), //Size
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

//Window Procedure
static LRESULT CALLBACK WindowProc(HWND Hwnd, UINT Msg, WPARAM Wparam, LPARAM Lparam)
{
	switch(Msg)
	{
	case WM_SETCURSOR:
		assert(proxywindow != nullptr);
		if(LOWORD(Lparam) == HTCLIENT && proxywindow->showcursor == true)
		{
			ShowCursor(false);
			proxywindow->showcursor = false;
		}
		if(LOWORD(Lparam) != HTCLIENT && proxywindow->showcursor == false)
		{
			ShowCursor(true);
			proxywindow->showcursor = true;
		}
		return 0;
	case WM_CLOSE:
		assert(proxywindow->hwnd != nullptr);
		DestroyWindow(proxywindow->hwnd);
		return 0;
	case WM_DESTROY:
		assert(proxywindow->hwnd != nullptr);
		proxywindow->Release();
		PostQuitMessage(0);
		proxywindow->hwnd = 0;
		proxywindow = nullptr;
		return 0;
	}

	return DefWindowProc(Hwnd, Msg, Wparam, Lparam);
}

//Constructor
Window::Window(HINSTANCE Hinstance, LPCWSTR Name, LPCWSTR ClassName, unsigned int Width, unsigned int Height):
hwnd(0),
hinstance(0),
classname(0),
displaymode(WINDOWED),
width(0),
height(0),
hdc(0),
showcursor(true)
{
	if(!EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &windowedsettings))
		throw std::runtime_error("Window - Failed to save display settings!\n");

	Create(Hinstance, Name, ClassName, Width, Height);
}

//Destructor
Window::~Window()
{
	assert(hwnd == 0);
}

//Create
void Window::Create(HINSTANCE Hinstance, LPCWSTR Name, LPCWSTR ClassName, unsigned int Width, unsigned int Height)
{
	assert(hwnd == 0);
	assert(Hinstance != 0);
	assert(WindowProc != nullptr);
	assert(Name != nullptr);
	
	if(Width == 0)
		Width = windowedsettings.dmPelsWidth;

	if(Height == 0)
		Height = windowedsettings.dmPelsHeight;

	width = Width;
	height = Height;

	hinstance = Hinstance;
	classname = ClassName;

	WNDCLASSEX c;
	memset(&c, 0, sizeof(c));

	c.cbSize = sizeof(c);
	c.hbrBackground = (HBRUSH)COLOR_WINDOW;
	c.hCursor = LoadCursor(0, IDC_ARROW);
	c.hInstance = Hinstance;
	c.style = CS_VREDRAW | CS_HREDRAW;
	c.lpfnWndProc = WindowProc;
	c.lpszClassName = ClassName;

	if(!RegisterClassEx(&c))
		throw std::runtime_error(std::string("Window - Failed to register window class!"));

	RECT client = { 0, 0, Width, Height };
	if(!AdjustWindowRect(&client, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, false))
		throw std::runtime_error("Window - Failed to adjust window size!");

	hwnd = CreateWindowEx(0, ClassName, Name, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 0, 0, client.right - client.left, client.bottom - client.top, 0, 0, Hinstance, 0); 

	if(hwnd == 0)
		throw std::runtime_error("Window - Failed to create window!");

	//Get Device Context
	hdc = GetDC(hwnd);

	if(hdc == 0)
		throw std::runtime_error("Window - Failed to get device context!");

	int pixelformatid = ChoosePixelFormat(hdc, &RGBA32);

	if(pixelformatid == 0)
	{
		ReleaseDC(hwnd, hdc);
		throw std::runtime_error("Window - Failed to find valid pixel format!");
	}

	if(!SetPixelFormat(hdc, pixelformatid, &RGBA32))
	{
		ReleaseDC(hwnd, hdc);
		throw std::runtime_error("Window - Failed to set pixel format!");
	}

	//Create rendering context
	contextlock.lock();

	if(windowsmade == 0)
		hrc = wglCreateContext(hdc);

	if(hrc == 0)
	{
		ReleaseDC(hwnd, hdc);
		throw std::runtime_error("Window - Failed to create rendering context!");
	}

	if(wglMakeCurrent(hdc, hrc) == false)
	{
		ReleaseDC(hwnd, hdc);
		wglDeleteContext(hrc);
		throw std::runtime_error("Window - Failed to set rendering context!");
	}

	//Initialize GLEW
	glewExperimental = true;
	GLenum error = glewInit();
	if(error != GLEW_OK)
	{
		ReleaseDC(hwnd, hdc);
		wglDeleteContext(hrc);
		throw std::runtime_error(std::string("Graphics - Failed to initialize GLEW! ").append((char*)glewGetErrorString(error)));
	}

	//Check OpenGL version
	if(!GLEW_VERSION_3_3)
	{
		ReleaseDC(hwnd, hdc);
		wglDeleteContext(hrc);
		throw std::runtime_error("Graphics - OpenGL 3.3 is not supported!");
	}

	//Load identity matrix into projection and modelview
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Set clear color
	glClearColor(0, 0, 0, 0);

	//Check for errors in OpenGL
	error = glGetError();
	if(error != GL_NO_ERROR)
	{
		ReleaseDC(hwnd, hdc);
		wglDeleteContext(hrc);
		throw std::runtime_error(std::string("Graphics - OpenGL initialization has failed! ").append((char*)glewGetErrorString(error)));
	}

	contextlock.unlock();

	++windowsmade;
}

//Bind As Render Target
bool Window::BindAsRenderTarget(bool Wait)
{
	if(Wait)
	{
		contextlock.lock();

		wglMakeCurrent(0, 0);

		if(!wglMakeCurrent(hdc, hrc))
			throw std::runtime_error("Window - Failed to set window as render target!");

		return true;
	}
	else
	{
		if(contextlock.try_lock())
		{
			wglMakeCurrent(0, 0);

			if(!wglMakeCurrent(hdc, hrc))
				throw std::runtime_error("Window - Failed to set window as render target!");

			return true;
		}
		return false;
	}
}

//Unbind As Render Target
void Window::UnbindAsRenderTarget()
{
	contextlock.unlock();
}

//Update
void Window::Update()
{
	if(hwnd == 0)
		throw std::runtime_error("Window - Failed to update window! Window has been closed!");

	proxywindow = this;

	MSG msg;
	while(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	SwapBuffers(hdc);
}

//Good
bool Window::Good()
{
	if(hwnd != 0)
		return true;
	else
		return false;
}

//Display Mode
void Window::DisplayMode(Window::DISPLAY_MODE Mode)
{
	if(hwnd == 0)
		throw std::runtime_error("Window - Failed to set display mode! Window has been closed!");

	if(displaymode == FULLSCREEN && Mode == FULLSCREEN)
		throw std::runtime_error("Window - Failed to set display mode! Already fullscreen!");

	if(displaymode == WINDOWED && Mode == WINDOWED)
		throw std::runtime_error("Window - Failed to set display mode! Already windowed!");

	switch(Mode)
	{
	case FULLSCREEN:
		DEVMODE settings;
		memset(&settings, 0, sizeof(settings));

		if(!EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &settings))
			throw std::runtime_error("Window - Failed to get display information!");

		if(pixelsize != 0)
			settings.dmBitsPerPel = pixelsize;
		settings.dmPelsWidth = width;
		settings.dmPelsHeight = height;
		settings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if(ChangeDisplaySettings(&settings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
			throw std::runtime_error("Window - Failed to set display mode to fullscreen!");

		if(!SetWindowLongPtr(hwnd, GWL_STYLE, WS_POPUP))
			throw std::runtime_error("Window - Failed to set window frame for fullscreen!");

		if(!SetWindowPos(hwnd, HWND_TOP, 0, 0, width, height, SWP_FRAMECHANGED | SWP_SHOWWINDOW))
			throw std::runtime_error("Window - Failed to set window position for fullscreen!");

		displaymode = Mode;
		break;
	case WINDOWED:
		if(ChangeDisplaySettings(&windowedsettings, 0) != DISP_CHANGE_SUCCESSFUL)
			throw std::runtime_error("Window - Failed to set display mode to windowed!");

		if(!SetWindowLongPtr(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW))
			throw std::runtime_error("Window - Failed to set window frame for windowed mode!");

		if(!SetWindowPos(hwnd, HWND_TOP, 0, 0, width, height, SWP_FRAMECHANGED | SWP_SHOWWINDOW))
			throw std::runtime_error("Window - Failed to set window position for windowed mode!");

		displaymode = Mode;
		break;
	case RESET:
		if(ChangeDisplaySettings(0, 0) != DISP_CHANGE_SUCCESSFUL)
			throw std::runtime_error("Window - Failed to reset display mode!");
		break;		
	}
}

//Resolution
void Window::SetResolution(unsigned int Width, unsigned int Height)
{
	if(hwnd == 0)
		throw std::runtime_error("Window - Failed to set resolution! Window has been closed!");

	assert(Width != 0);
	assert(Height != 0);

	width = Width;
	height = Height;

	DisplayMode(RESET);
}

//Get Resolutions
void Window::GetResolutions(std::list<Resolution> &Target)
{
	DEVMODE mode;
	Resolution res;

	for(unsigned int count = 0; EnumDisplaySettings(0, count, &mode) != 0; ++count)
	{
		res.width = mode.dmPelsWidth;
		res.height = mode.dmPelsHeight;
		Target.push_back(res);
	}

	if(Target.size() == 0)
		throw std::runtime_error("Window - Failed to get resolution list! No resolutions found!");
}

//Show
void Window::Show()
{
	if(hwnd == 0)
		throw std::runtime_error("Window - Failed to show window! Window has been closed!");

	ShowWindow(hwnd, SW_SHOW);
}

//Hide
void Window::Hide()
{
	if(hwnd == 0)
		throw std::runtime_error("Window - Failed to hide window! Window has been closed!");

	ShowWindow(hwnd, SW_HIDE);
}

//Close
void Window::Close()
{
	if(hwnd == 0)
		throw std::runtime_error("Window - Failed to close window! Window has already been closed!");

	CloseWindow(hwnd);
}

//Release
void Window::Release()
{
	if(hwnd == 0)
		throw std::runtime_error("Window - Failed to release window! Window has already been closed");

	ReleaseDC(hwnd, hdc);
	UnregisterClass(classname, hinstance);
	--windowsmade;

	if(windowsmade == 0)
	{
		wglMakeCurrent(0, 0);
		wglDeleteContext(hrc);
	}
}

//Hide Mouse
void Window::HideMouse(bool State)
{
	showcursor = !State;
}

}