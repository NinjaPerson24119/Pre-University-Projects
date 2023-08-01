#ifndef CTM_TEXTURE_H
#define CTM_TEXTURE_H

#include "../External/OpenGL.h"
#include "../External/DevIL.h"
#include "../Base/Base.h"
#include "cColor.h"
#include "../Data/cHeapAllocator.h"
#include "../Data/cString.h"
#include "../Math/MathGeneralFunctions.h"

namespace ctm
{

///////////////////////
//Texture vertex struct
class texvertex
{
public:
	GLfloat x, y;
	GLfloat s, t;
};
///////////////////////

///////////////////////
//Texture class
class texture
{
public:
	//System
		texture(heapallocator *iAlloc);
		texture(texture &rhs);
		virtual ~texture();
		texture &operator=(texture &rhs); //Operator =
		bool load_texture(unsigned int *iPixels, unsigned int iTexWidth, unsigned int iTexHeight, unsigned int iImgWidth = 0, unsigned int iImgHeight = 0); //Loads a texture from a block of RGBA values (Make sure to pad iPixels before loading)
		bool load_texture(GLubyte *iPixels, unsigned int iTexWidth, unsigned int iTexHeight, unsigned int iImgWidth = 0, unsigned int iImgHeight = 0); //Loads a texture from a block of alpha values
		bool load_texture(string &iFilename); //Loads a texture from a file
		bool load_texture(unsigned int iWidth, unsigned int iHeight); //Loads an empty texture of the specified size
		bool load_texture(unsigned int iWidth, unsigned int iHeight, unsigned int iData); //Loads an empty texture and fills it with an integer pixel
		bool load_texture(unsigned int iWidth, unsigned int iHeight, color iBrush); //Loads an empty texture and fills it with a color
		virtual void free_texture(); //Deletes any existing texture data
		void draw_texture(float x, float y); //Draws the texture
	//Editing
		void bind_texture(); //Binds the texture for operations
		void unbind_texture(); //Unbinds the texture and applies changes
		void blit_texture(unsigned int x, unsigned int y, texture &target); //Copies texture data to target texture at given coordinates
		void pad_texture(); //Resizes the texture to the lowest power of 2
		unsigned int get_pixel(unsigned int x, unsigned int y); //Returns an integer pixel from the texture data
		color get_color(unsigned int x, unsigned int y); //Returns a color from the texture data
		void set_pixel(unsigned int x, unsigned int y, unsigned int nData); //Sets a pixel from an integer pixel
		void set_color(unsigned int x, unsigned int y, color brush); //Sets a pixel from a color
	//Buffers
		void init_buffers(); //Initializes buffers
		void free_buffers(); //Deletes any existing buffers
	//Get
		unsigned int get_texwidth() { return texwidth; } //Returns the width of the texture (Padded)
		unsigned int get_texheight() { return texheight; } //Returns the height of the texture (Padded)
		unsigned int get_imgwidth() { return imgwidth; } //Returns the width of the texture (Actual)
		unsigned int get_imgheight() { return imgheight; } //Returns the height of the texture (Actual)
		unsigned int get_id() { return id; } //Returns the texture id
private:
	//Inaccessible
		unsigned int *pad_pixels(unsigned int *data, unsigned int &texwidth, unsigned int &texheight, unsigned int &imgwidth, unsigned int &imgheight); //Resizes an array of pixels to the lowest power of 2
	//Data
		unsigned int texwidth; //Width of texture (Padded image dimension)
		unsigned int texheight; //Height of texture (Padded image dimension)
		unsigned int imgwidth; //Width of texture (Actual image dimension)
		unsigned int imgheight; //Height of texture (Actual image dimension)
		unsigned int id; //Texture ID
		unsigned int *data; //Texture data
		unsigned int binded; //Texture editing state
	//Buffers
		unsigned int vboid; //Vertex buffer id
		unsigned int iboid; //Indice buffer id
	//Allocation
		heapallocator *alloc; //Allocator
};
///////////////////////

//Other functions
unsigned int color_to_pixel(color brush); //Converts a color into an integer pixel
color pixel_to_color(unsigned int pixel); //Converts an integer pixel into a color

}

#endif