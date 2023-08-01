#ifndef CTM_WINDOW_H
#define CTM_WINDOW_H

#include <Windows.h>
#include <windowsx.h>
#include <mutex>

#include <list>

namespace ctm
{

LRESULT CALLBACK WindowProc(HWND Hwnd, UINT Msg, WPARAM Wparam, LPARAM Lparam); 

//////
//Window
class Window
{
	friend LRESULT CALLBACK WindowProc(HWND Hwnd, UINT Msg, WPARAM Wparam, LPARAM Lparam);
public:
	//Resolution
		class Resolution
		{
		public:
			unsigned int width, height;
		};
	//Display Modes
		enum DISPLAY_MODE { FULLSCREEN, WINDOWED, RESET };
	//Pixel Formats
		static PIXELFORMATDESCRIPTOR RGBA32; //RGBA 32-Bit 
	//Base
		Window(HINSTANCE Hinstance, LPCWSTR Name, LPCWSTR ClassName, unsigned int Width = 0, unsigned int Height = 0);
		~Window();
	//Functionality
		bool BindAsRenderTarget(bool Wait = true);
		void UnbindAsRenderTarget();
		void Show();
		void Hide();
		void Close(); //Requires Update() to complete
		void Update();
		bool Good();
		void HideMouse(bool State);
		void DisplayMode(DISPLAY_MODE Mode);
		void SetResolution(unsigned int Width, unsigned int Height);
	//Get
		DISPLAY_MODE GetDisplayMode() { return displaymode; }
		unsigned int Width() { return width; }
		unsigned int Height() { return height; }
		void GetResolutions(std::list<Resolution> &Target);
private:
	//Inaccessible
		Window(Window &Rhs);
		Window &operator=(Window &Rhs);
		void Create(HINSTANCE Hinstance, LPCWSTR Name, LPCWSTR ClassName, unsigned int Width = 0, unsigned int Height = 0); //Windowed
		void Release();
	HWND hwnd;
	HINSTANCE hinstance;
	LPCWSTR classname;
	unsigned int width, height;
	DEVMODE windowedsettings;
	DISPLAY_MODE displaymode;
	HDC hdc;
	static HGLRC hrc;
	static uintptr_t windowsmade;
	bool showcursor;
};
//////

}

#endif