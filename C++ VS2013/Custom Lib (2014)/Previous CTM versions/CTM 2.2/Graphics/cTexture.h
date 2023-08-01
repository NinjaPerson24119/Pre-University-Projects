#ifndef CTM_TEXTURE_H
#define CTM_TEXTURE_H

#include "../External/OpenGL.h"
#include "../External/DevIL.h"
#include "../Base/Base.h"
#include "../Data/cHeapAllocator.h"
#include "../Data/cString.h"

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
		BOOL8 load_texture(GLuint *iPixels, GLuint iTexWidth, GLuint iTexHeight, GLuint iImgWidth = 0, GLuint iImgHeight = 0); //Loads a texture from a block of RGBA values (Make sure to pad iPixels before loading)
		BOOL8 load_texture(GLubyte *iPixels, GLuint iTexWidth, GLuint iTexHeight, GLuint iImgWidth = 0, GLuint iImgHeight = 0); //Loads a texture from a block of alpha values
		BOOL8 load_texture(string &iFilename); //Loads a texture from a file
		BOOL8 load_texture(UINT32 iWidth, UINT32 iHeight); //Loads an empty texture of the specified size
		BOOL8 load_texture(UINT32 iWidth, UINT32 iHeight, GLuint iData); //Loads an empty texture and fills it with an integer pixel
		BOOL8 load_texture(UINT32 iWidth, UINT32 iHeight, color iBrush); //Loads an empty texture and fills it with a color
		virtual void free_texture(); //Deletes any existing texture data
		void draw_texture(FLOAT32 x, FLOAT32 y); //Draws the texture
	//Editing
		void bind_texture(); //Binds the texture for operations
		void unbind_texture(); //Unbinds the texture and applies changes
		void blit_texture(UINT32 x, UINT32 y, texture &target); //Copies texture data to target texture at given coordinates
		void pad_texture(); //Resizes the texture to the lowest power of 2
		GLuint get_pixel(UINT32 x, UINT32 y); //Returns an integer pixel from the texture data
		color get_color(UINT32 x, UINT32 y); //Returns a color from the texture data
		void set_pixel(UINT32 x, UINT32 y, GLuint nData); //Sets a pixel from an integer pixel
		void set_color(UINT32 x, UINT32 y, color brush); //Sets a pixel from a color
	//Buffers
		void init_buffers(); //Initializes buffers
		void free_buffers(); //Deletes any existing buffers
	//Get
		GLuint get_texwidth() { return texwidth; } //Returns the width of the texture (Padded)
		GLuint get_texheight() { return texheight; } //Returns the height of the texture (Padded)
		GLuint get_imgwidth() { return imgwidth; } //Returns the width of the texture (Actual)
		GLuint get_imgheight() { return imgheight; } //Returns the height of the texture (Actual)
		GLuint get_id() { return id; } //Returns the texture id
private:
	//Inaccessible
		GLuint *pad_pixels(GLuint *data, GLuint &texwidth, GLuint &texheight, GLuint &imgwidth, GLuint &imgheight); //Resizes an array of pixels to the lowest power of 2
	//Data
		GLuint texwidth; //Width of texture (Padded image dimension)
		GLuint texheight; //Height of texture (Padded image dimension)
		GLuint imgwidth; //Width of texture (Actual image dimension)
		GLuint imgheight; //Height of texture (Actual image dimension)
		GLuint id; //Texture ID
		GLuint *data; //Texture data
		GLuint binded; //Texture editing state
	//Buffers
		GLuint vboid; //Vertex buffer id
		GLuint iboid; //Indice buffer id
	//Allocation
		heapallocator *alloc; //Allocator
};
///////////////////////

//Other functions
GLuint color_to_pixel(color brush); //Converts a color into an integer pixel
color pixel_to_color(GLuint pixel); //Converts an integer pixel into a color

}

#endif