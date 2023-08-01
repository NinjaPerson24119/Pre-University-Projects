#ifndef TEXTURE_H
#define TEXTURE_H

#ifndef STRING
#define STRING
#include <string>
#endif

//Warning: Textures tend not to work in vectors, instead use a pointer to texture vector type

///////////////////////
//Texture class
class texture
{
public:
	//System
		texture();
		texture(const std::string iFilename);
		~texture();
		bool load_texture(GLuint *iPixels, GLuint iWidth, GLuint iHeight);
		bool load_texture(const std::string iFilename);
		void free_texture();
		void draw_texture(float x, float y, float scalewidth, float scaleheight);
	//Get
		GLuint get_width() { return width; }
		GLuint get_height() { return height; }
		GLuint get_id() { return id; }
private:
	//Data
		GLuint width; //Width of texture
		GLuint height; //Height of texture
		GLuint id; //Texture ID
		GLuint *modified; //Holds modified texture
};

//Constructor
texture::texture():
width(0),
height(0),
id(0),
modified(0) {}

texture::texture(const std::string iFilename):
width(0),
height(0),
id(0),
modified(0)
{
	load_texture(iFilename);
}

//Destructor
texture::~texture()
{
	free_texture();
	if(modified != 0) { delete modified; modified = 0; }
}

//Load texture from pixels
bool texture::load_texture(GLuint *iPixels, GLuint iWidth, GLuint iHeight)
{	
	free_texture(); //Free texture if existant

	width = iWidth; //Set dimensions
	height = iHeight;

	glEnable(GL_TEXTURE_2D);

	glGenTextures(1,&id); //Generate texture id
	glBindTexture(GL_TEXTURE_2D,id); //Bind texture
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); //Set image traits
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,iPixels); //Load texture
	glBindTexture(GL_TEXTURE_2D,0); //Unbind texture

	glDisable(GL_TEXTURE_2D);

	GLenum error = glGetError(); //Check for errors
	if(error != GL_NO_ERROR)
	{
		std::cout << "Failed to load texture! Error: " << gluErrorString(error) << "\n";
		return false;
	}
	return true;
}

//Load texture from file
bool texture::load_texture(const std::string iFilename)
{
	ILuint image = 0;
	ilGenImages(1,&image); //Generate image id
	ilBindImage(image); //Bind image
	ilOriginFunc(IL_ORIGIN_UPPER_LEFT); //Set origin to upper left
	if(ilLoadImage(iFilename.c_str()) == false) //Check for errors
	{
		ILenum error = ilGetError();
		std::cout << "Failed to load image! Error: " << error << "\n";
		return false;
	}
	ilConvertImage(IL_RGBA,IL_UNSIGNED_BYTE); //Convert image to RGBA

	load_texture((GLuint*)ilGetData(),ilGetInteger(IL_IMAGE_WIDTH),ilGetInteger(IL_IMAGE_HEIGHT)); //Load image into texture

	//Cleanup
	ilDeleteImages(1,&image); //Delete image id
	
	return true;
}

//Free texture
void texture::free_texture()
{
	//Check that texture exists
	if(id != 0)
	{
		glDeleteTextures(1,&id); //Delete texture
		id = 0;
	}
	width = 0;
	height = 0;
}

//Draw texture
void texture::draw_texture(float x, float y, float scalewidth = -1, float scaleheight = -1)
{
	//Check if texture exists
	if(id != 0)
	{
		//Defaults
		if(scalewidth == -1) scalewidth = (float)width;
		if(scaleheight == -1) scaleheight = (float)height;

		glEnable(GL_TEXTURE_2D); //Enable texturing
			glBindTexture(GL_TEXTURE_2D,id); //Bind texture
				glBegin(GL_QUADS);
					glTexCoord2f(0.f,0.f); glVertex2f(x,y);
					glTexCoord2f(1.f,0.f); glVertex2f(x+scalewidth,y);
					glTexCoord2f(1.f,1.f); glVertex2f(x+scalewidth,y+scaleheight);
					glTexCoord2f(0.f,1.f); glVertex2f(x,y+scaleheight);
				glEnd();
			glBindTexture(GL_TEXTURE_2D,0); //Unbind texture
		glDisable(GL_TEXTURE_2D); //Disable texturing
	}
}
///////////////////////

#endif