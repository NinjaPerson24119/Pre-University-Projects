#include "cFont.h"
#include FT_BITMAP_H

INT32 DEFAULT_TAB_SPACES = 8;

//Constructor
font::font():
x(0),
y(0),
charwidth(0),
charheight(0),
charhang(0)
{}

//Loads a font using freetype
BOOL8 font::load_font(string iFilename, UINT32 pixelsize)
{
	//Free font if existant
	free_font();

	//Initialize FreeType
	FT_Library lib;
	FT_Error error = FT_Init_FreeType(&lib);
	
	#ifdef CUSTOMLIB_DEBUG_FAST
		if(DEFAULT_DEBUGLOG != 0)
			if(error)
			{
				DEFAULT_DEBUGLOG->send_error("Error: cFont - Failed to initialize FreeType!\n",false);
				return false;
			}
	#endif

	//Load face
	FT_Face face;
	error = FT_New_Face(lib,iFilename.get_char(),0,&face);

	#ifdef CUSTOMLIB_DEBUG_FAST
		if(DEFAULT_DEBUGLOG != 0)
			if(error)
			{
				DEFAULT_DEBUGLOG->send_error("Error: cFont - Failed to load face!\n",false);
				FT_Done_FreeType(lib);
				return false;
			}
	#endif

	//Scale face
	error = FT_Set_Pixel_Sizes(face,pixelsize,pixelsize);

	#ifdef CUSTOMLIB_DEBUG_FAST
		if(DEFAULT_DEBUGLOG != 0)
			if(error)
			{
				DEFAULT_DEBUGLOG->send_error("Error: cFont - Failed to scale face!\n",false);
				FT_Done_Face(face);
				FT_Done_FreeType(lib);
				return false;
			}
	#endif

	//Load character data
	FT_Glyph_Metrics metrics[256];
	texture imgs[256];
	UINT32 maxcellwidth = 0;
	UINT32 maxcellheight = 0;
	UINT32 maxbearing = 0;
	UINT32 maxhang = 0;

	for(UINT32 count = 0; count < 256; ++count)
	{
		error = FT_Load_Char(face,count,FT_LOAD_RENDER); //Load next character

		#ifdef CUSTOMLIB_DEBUG_FAST
			if(DEFAULT_DEBUGLOG)
				if(error)
				{
					DEFAULT_DEBUGLOG->send_error("Error: cFont - Failed to load character!\n",false);
					FT_Done_Face(face);
					FT_Done_FreeType(lib);
					return false;
				}
		#endif

		metrics[count] = face->glyph->metrics;
		imgs[count].load_texture(face->glyph->bitmap.buffer,face->glyph->bitmap.width,face->glyph->bitmap.rows);

		//Calculate width
		if(metrics[count].width/72 > maxcellwidth)
			maxcellwidth = metrics[count].width/72;

		//Calculate bearing
		if(metrics[count].horiBearingY/72 > maxbearing)
			maxbearing = metrics[count].horiBearingY/72;

		//Calculate hang
		if((metrics[count].height - metrics[count].horiBearingY)/72 > maxhang)
			maxhang = (metrics[count].height - metrics[count].horiBearingY)/72;
	}

	//Create character sheet
	maxcellheight = maxbearing+maxhang; //Calculate cell height
	charsheet.load_texture(16*maxcellwidth,16*maxcellheight); //Load empty texture
	charsheet.bind_texture(); //Bind texture for operations

	//Setup sprite sheet
	rect region(0,0,0,0); //Clip region
	for(UINT32 x = 0; x < 16; ++x)
	{
		for(UINT32 y = 0; y < 16; ++y)
		{
			//Set clip region
			region.left = x*maxcellwidth;
			region.top = y*maxcellheight;
			region.right = region.left + maxcellwidth;
			region.bottom = region.top + maxcellheight;

			//Blit character
			imgs[y*16+x].bind_texture(); //Bind character image for operations
			imgs[y*16+x].blit_texture(x*maxcellwidth,y*maxcellheight,charsheet); //Blit character
			imgs[y*16+x].unbind_texture(); //Unbind character image

			//Set clip region
			charsheet.add_clip(region);
		}
	}

	//Finalize character sheet
	charsheet.unbind_texture(); //Unbind texture
	charsheet.update_clips(); //Update clips

	//Set spacing variable
	charwidth = maxcellwidth;
	charheight = maxcellheight;
	charhang = maxhang;

	//Free face
	FT_Done_Face(face);

	//Free FreeType
	FT_Done_FreeType(lib);

	return true;
}

//Free font
void font::free_font()
{
	//Reset pen
	x = 0;
	y = 0;

	//Reset font data
	charwidth = 0;
	charheight = 0; 
	charhang = 0;

	//Free character sheet
	charsheet.free_texture();
}

//Draw font
void font::draw_font(INT32 x, INT32 y)
{
	#ifdef CUSTOMLIB_DEBUG
		if(charsheet.get_clipcount() == 0)
			std::cout << "Error: cFont - Failed to draw font! Font has not been loaded!\n";
	#endif

	charsheet.draw_texture((FLOAT32)x,(FLOAT32)y);
}

//Text
void font::text(string data)
{
	#ifdef CUSTOMLIB_DEBUG
		if(charsheet.get_clipcount() == 0)
			std::cout << "Error: cFont - Failed to draw text! Font has not been loaded!\n";
	#endif

	INT32 linestartx = x; //Store x position (X is restored on newlines)

	//Scroll string contents
	for(UINT32 count = 0; count < data.get_size(); ++count)
	{
		switch(data.at(count))
		{
		case '\'':
			charsheet.draw_clip(x,y,39);
			x += charwidth;
			break;
		case '\"':
			charsheet.draw_clip(x,y,34);
			x += charwidth;
			break;
		case '\?':
			charsheet.draw_clip(x,y,63);
			x += charwidth;
			break;
		case '\\':
			charsheet.draw_clip(x,y,92);
			x += charwidth;
			break;
		case '\n':
			x = linestartx; //Restore original x position
			y += charheight + charhang;
			break;
		case '\t':
			x += DEFAULT_TAB_SPACES*charwidth;
			break;
		default:
			charsheet.draw_clip(x,y,(UINT32)data.at(count));
			x += charheight;
			break;
		}
	}
}

//Text (Pen reposition)
void font::text(string data, INT32 nX, INT32 nY)
{
	set_pen(nX,nY); //Move pen
	text(data); //Write text normally
}

//Set cursor
void font::set_pen(INT32 nX, INT32 nY)
{
	x = nX;
	y = nY;
}