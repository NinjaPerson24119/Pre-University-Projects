#ifndef FONT_H
#define FONT_H

#include "../../FreeType.h"
#include "../Base/Base.h"
#include "cTextureSheet.h"
#include "../Data/cString.h"

extern INT32 DEFAULT_TAB_SPACES;

////////////////////////
//Font class
class font
{
public:
	//System
		font();
		BOOL8 load_font(string iFilename, UINT32 pixelsize); //Loads a font using FreeType
		void free_font(); //Deletes the font if existing
	//Drawing
		void draw_font(INT32 x, INT32 y); //Draws the entire font
		void text(string data); //Prints a string
		void text(string data, INT32 nX, INT32 nY); //Moves the pen and prints a string
		void set_pen(INT32 nX, INT32 nY); //Moves the pen
	//Get
		UINT32 get_charcount() { return charsheet.get_clipcount(); }
private:
	texturesheet charsheet; //Character sheet
	INT32 x, y; //Pen position
	UINT32 charwidth; //Width of each character
	UINT32 charheight; //Height of each character
	UINT32 charhang; //Longest characters overhang
};
////////////////////////

#endif