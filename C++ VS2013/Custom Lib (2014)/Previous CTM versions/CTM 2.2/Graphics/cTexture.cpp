#include "cTexture.h"

namespace ctm
{

//Constructor
texture::texture(heapallocator *iAlloc):
texwidth(0),
texheight(0),
imgwidth(0),
imgheight(0),
id(0),
data(0),
binded(0),
vboid(0),
iboid(0),
alloc(iAlloc) {}

//Copy constructor
texture::texture(texture &rhs):
texwidth(0),
texheight(0),
imgwidth(0),
imgheight(0),
id(0),
data(0),
binded(0),	
vboid(0),
iboid(0)
{
	//Check that data exists to copy
	if(rhs.id != 0)
	{
		GLuint oldbinded = rhs.binded; //Store bind state
		if(rhs.binded == 0) rhs.bind_texture(); //Bind texture if not binded already
		load_texture(rhs.data,rhs.texwidth,rhs.texheight,rhs.imgwidth,rhs.imgheight);
		if(oldbinded == 0) rhs.unbind_texture(); //Revert texture to previous bind state
	}
}

//Operator =
texture &texture::operator=(texture &rhs)
{
	texwidth = 0;
	texheight = 0;
	imgwidth = 0;
	imgheight = 0;
	id = 0;
	data = 0;
	binded = 0;
	vboid = 0;
	iboid = 0;

	//Check that data exists to copy
	if(rhs.id != 0)
	{
		GLuint oldbinded = rhs.binded; //Store bind state
		if(rhs.binded == 0) rhs.bind_texture(); //Bind texture if not binded already
		load_texture(rhs.data,rhs.texwidth,rhs.texheight,rhs.imgwidth,rhs.imgheight);
		if(oldbinded == 0) rhs.unbind_texture(); //Revert texture to previous bind state
	}
	return *this;
}

//Destructor
texture::~texture()
{
	free_texture();
	free_buffers();
}

//Load texture from pixels (RGBA)
BOOL8 texture::load_texture(GLuint *iPixels, GLuint iTexWidth, GLuint iTexHeight, GLuint iImgWidth, GLuint iImgHeight)
{	
	free_texture(); //Free texture if existant

	//Set defaults
	if(iImgWidth == 0) iImgWidth = iTexWidth;
	if(iImgHeight == 0) iImgHeight = iTexHeight;

	//Set dimensions
	texwidth = iTexWidth;
	texheight = iTexHeight;
	imgwidth = iImgWidth;
	imgheight = iImgHeight;

	glGenTextures(1,&id); //Generate texture id
	glBindTexture(GL_TEXTURE_2D,id); //Bind texture
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); //Set image traits
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,texwidth,texheight,0,GL_RGBA,GL_UNSIGNED_BYTE,iPixels); //Load texture
	glBindTexture(GL_TEXTURE_2D,0); //Unbind texture

	GLenum error = glGetError();
	if(error != GL_NO_ERROR)
	{
		#ifdef CTM_DEBUG_FAST
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cTexture - Failed to load texture from pixel data!\n",false);
		#endif
		return false;
	}

	init_buffers(); //Initialize buffers
	return true;
}

//Load texture from pixels (ALPHA)
BOOL8 texture::load_texture(GLubyte *data, GLuint iTexWidth, GLuint iTexHeight, GLuint iImgWidth, GLuint iImgHeight)
{
	//Set defaults
	if(iImgWidth == 0) iImgWidth = iTexWidth;
	if(iImgHeight == 0) iImgHeight = iTexHeight;

	//Allocate new RGBA data
	GLuint *newdata = 0;
	if(alloc == 0)
		newdata = new GLuint[iTexWidth*iTexHeight];
	else
		newdata = (GLuint*)alloc->allocate(sizeof(GLuint)*iTexWidth*iTexHeight);

	//Convert and copy ALPHA pixels to RGBA pixel array
	GLuint paint = 0; //Color integer
	GLubyte *temp = 0; //Channel changer

	for(UINT32 count = 0; count < iTexWidth*iTexHeight; ++count)
	{
		//Set color integer
		temp = (GLubyte*)&paint; //Ready channel changer
		temp[0] = 0;
		temp[1] = 0;
		temp[2] = 0;
		temp[3] = data[count];

		//Apply color
		newdata[count] = paint;
	}

	newdata = pad_pixels(newdata,texwidth,texheight,imgwidth,imgheight); //Pad data
	BOOL8 flag = load_texture(newdata,iTexHeight,iTexWidth,iImgWidth,iImgHeight); //Load texture as RGBA
	
	//Deallocate RGBA data
	if(alloc == 0)
		delete[] newdata;
	else
		alloc->deallocate((void*)newdata);

	return flag;
}

//Load texture from file
BOOL8 texture::load_texture(string &iFilename)
{
	ILuint image = 0;
	ilGenImages(1,&image); //Generate image id
	ilBindImage(image); //Bind image
	ilOriginFunc(IL_ORIGIN_UPPER_LEFT); //Set origin to upper left
	if(ilLoadImage(iFilename.get_cstr()) == false) //Check for errors
	{
		#ifdef CTM_DEBUG_FAST
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cTexture - Failed to load texture from file!\n",false);
		#endif
		return false;
	}
	if(ilConvertImage(IL_RGBA,IL_UNSIGNED_BYTE) == false) //Convert image to RGBA
	{
		#ifdef CTM_DEBUG_FAST
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cTexture - Failed to load texture from file!\n",false);
		#endif
		return false;
	}

	//Set dimensions
	imgwidth = ilGetInteger(IL_IMAGE_WIDTH);
	imgheight = ilGetInteger(IL_IMAGE_HEIGHT);
	texwidth = lowestpow2(imgwidth);
	texheight = lowestpow2(imgheight);

	//Pad texture if needed
	if((imgwidth != texwidth) || (imgheight != texheight))
	{
		iluImageParameter(ILU_PLACEMENT,ILU_UPPER_LEFT); //Set ILU origin to top left
		iluEnlargeCanvas(texwidth,texheight,1); //Resize image
	}

	load_texture((GLuint*)ilGetData(),texwidth,texheight,imgwidth,imgheight); //Load image into texture

	//Cleanup
	ilDeleteImages(1,&image); //Delete image id
	return true;
}

//Loads empty texture
BOOL8 texture::load_texture(UINT32 iWidth, UINT32 iHeight)
{
	//Set dimensions
	texwidth = iWidth;
	texheight = iHeight;
	imgwidth = iWidth;
	imgheight = iHeight;

	//Allocate data
	GLuint *data = 0;
	if(alloc == 0)
		data = new GLuint[iWidth*iHeight];
	else
		data = (GLuint*)alloc->allocate(sizeof(GLuint)*iWidth*iHeight);

	//Initialize data
	for(UINT32 count = 0; count < iWidth*iHeight; ++count)
	{
		data[count] = 0;
	}

	data = pad_pixels(data,texwidth,texheight,imgwidth,imgheight); //Pad data
	BOOL8 flag = load_texture(data,texwidth,texheight,imgwidth,imgheight); //Load texture
	
	//Deallocate data
	if(alloc == 0)
		delete[] data;
	else
		alloc->deallocate((void*)data);

	return flag;
}

//Loads an integer pixel initialized texture
BOOL8 texture::load_texture(UINT32 iWidth, UINT32 iHeight, GLuint iData)
{
	//Set dimensions
	texwidth = iWidth;
	texheight = iHeight;
	imgwidth = iWidth;
	imgheight = iHeight;

	//Allocate data
	GLuint *data = 0;
	if(alloc == 0)
		data = new GLuint[iWidth*iHeight];
	else
		data = (GLuint*)alloc->allocate(sizeof(GLuint)*iWidth*iHeight);

	//Initialize data
	for(UINT32 count = 0; count < iWidth*iHeight; ++count)
	{
		data[count] = iData;
	}

	data = pad_pixels(data,texwidth,texheight,imgwidth,imgheight); //Pad data
	BOOL8 flag = load_texture(data,texwidth,texheight,imgwidth,imgheight); //Load texture
	
	//Deallocate data
	if(alloc == 0)
		delete[] data;
	else
		alloc->deallocate((void*)data);

	return flag;
}

//Loads a color initialized texture
BOOL8 texture::load_texture(UINT32 iWidth, UINT32 iHeight, color iBrush)
{
	//Set dimensions
	texwidth = iWidth;
	texheight = iHeight;
	imgwidth = iWidth;
	imgheight = iHeight;

	//Allocate data
	GLuint *data = 0; 
	if(alloc == 0)
		data = new GLuint[iWidth*iHeight];
	else
		data = (GLuint*)alloc->allocate(sizeof(GLuint)*iWidth*iHeight);

	//Initialize data
	GLuint iData = color_to_pixel(iBrush); //Convert color to integer pixel
	for(UINT32 count = 0; count < iWidth*iHeight; ++count)
	{
		data[count] = iData;
	}

	data = pad_pixels(data,texwidth,texheight,imgwidth,imgheight); //Pad data
	BOOL8 flag = load_texture(data,texwidth,texheight,imgwidth,imgheight); //Load texture
	
	//Deallocate data
	if(alloc == 0)
		delete[] data;
	else
		alloc->deallocate((void*)data);

	return flag;
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
	
	//Reset dimensions
	texwidth = 0;
	texheight = 0;
	imgwidth = 0;
	imgheight = 0;

	//Delete texture data
	if(data != 0)
		if(alloc == 0)
			delete[] data;
		else
			alloc->deallocate((void*)data);
	data = 0;

	//Reset bind state
	binded = 0;
}

//Draw texture
void texture::draw_texture(FLOAT32 x, FLOAT32 y)
{
	#ifdef CTM_DEBUG_SLOW
		if(id == 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cTexture - Failed to draw texture! Texture has not been loaded!\n",true);
		}
	#endif
		
	FLOAT32 quadleft = 0;
	FLOAT32 quadtop = 0;
	FLOAT32 quadright = (FLOAT32)imgwidth/(FLOAT32)texwidth;
	FLOAT32 quadbottom = (FLOAT32)imgheight/(FLOAT32)texheight;

	//Set vertices
	texvertex vertices[4]; 

	vertices[0].s = quadleft;
	vertices[0].t = quadtop;
	vertices[1].s = quadright;
	vertices[1].t = quadtop;
	vertices[2].s = quadright;
	vertices[2].t = quadbottom;
	vertices[3].s = quadleft;
	vertices[3].t = quadbottom;

	vertices[0].x = x;
	vertices[0].y = y;
	vertices[1].x = x + imgwidth;
	vertices[1].y = y;
	vertices[2].x = x + imgwidth;
	vertices[2].y = y + imgheight;
	vertices[3].x = x;
	vertices[3].y = y + imgheight;

	glBindTexture(GL_TEXTURE_2D,id); //Bind texture
		
	glEnableClientState(GL_VERTEX_ARRAY); //Enable vertex arrays
	glEnableClientState(GL_TEXTURE_COORD_ARRAY); //Enable texture coordinate arrays
	glBindBuffer(GL_ARRAY_BUFFER,vboid); //Bind vertex buffer
	glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(texvertex)*4,vertices); //Update buffer
	glTexCoordPointer(2,GL_FLOAT,sizeof(texvertex),(GLvoid*)offsetof(texvertex,s)); //Set texture coordinate data
	glVertexPointer(2,GL_FLOAT,sizeof(texvertex),(GLvoid*)offsetof(texvertex,x)); //Set vertex coordinate data

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,iboid); //Bind indice buffer
	glDrawElements(GL_QUADS,4,GL_UNSIGNED_INT,0); //Draw texture

	glDisableClientState(GL_TEXTURE_COORD_ARRAY); //Disable texture coordinate arrays
	glDisableClientState(GL_VERTEX_ARRAY); //Disable vertex arrays
}

//Bind texture
void texture::bind_texture()
{
	#ifdef CTM_DEBUG_FAST
	if(id == 0)
	{
		if(DEFAULT_DEBUGLOG != 0)
			DEFAULT_DEBUGLOG->send("Error: cTexture - Failed to bind texture! Texture has not been loaded!\n",true);
		assert(0);
	}
	if(binded == 1)
	{
		if(DEFAULT_DEBUGLOG != 0)
			DEFAULT_DEBUGLOG->send("Error: cTexture - Failed to bind texture ! Texture is already binded!\n",true);
		assert(0);
	}
	#endif

	//Allocate texture data
	GLuint size = texwidth*texheight;

	if(alloc == 0)
		data = new GLuint[size];
	else
		data = (GLuint*)alloc->allocate(sizeof(GLuint)*size);

	//Retrieve texture data
	glBindTexture(GL_TEXTURE_2D,id); //Bind texture
	glGetTexImage(GL_TEXTURE_2D,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
	glBindTexture(GL_TEXTURE_2D,0); //Unbind texture

	//Register bind
	binded = 1;
}

//Unbind texture
void texture::unbind_texture()
{
	#ifdef CTM_DEBUG_FAST
		if(id == 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cTexture - Failed to unbind texture! Texture is not binded!\n",true);
			assert(0);
		}
	#endif

	//Finalize texture
	glBindTexture(GL_TEXTURE_2D,id); //Bind texture
	glTexSubImage2D(GL_TEXTURE_2D,0,0,0,texwidth,texheight,GL_RGBA,GL_UNSIGNED_BYTE,data);
	glBindTexture(GL_TEXTURE_2D,0); //Unbind texture

	//Delete temporary data
	if(alloc == 0)
		delete[] data;
	else
		alloc->deallocate((void*)data);
	data = 0;

	//Register unbind
	binded = 0;
}

//Blit texture
void texture::blit_texture(UINT32 x, UINT32 y, texture &target)
{
	#ifdef CTM_DEBUG_FAST
		if(binded == 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cTexture - Failed to blit texture! Texture is not binded!\n",true);
			assert(0);
		}
	#endif

	#ifdef CTM_DEBUG_FAST
		if(target.binded == 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cTexture - Failed to blit texture! Target texture is not binded!\n",true);
			assert(0);
		}
	#endif

	#ifdef CTM_DEBUG_FAST
		if((x+imgwidth > target.imgwidth) || (y+imgheight > target.imgheight))
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cTexture - Failed to blit texture! Blitting coordinates are out of range!\n",true);
			assert(0);
		}
	#endif

	//Check that both textures are binded
	if((data != 0) && (target.data != 0))
	{
		//Copy data
		for(UINT32 count = 0; count < imgheight; ++count)
		{
			memcpy(&target.data[(count+y)*target.texwidth+x],&data[count*texwidth],imgwidth*4);
		}
	}
}

//Pad texture
void texture::pad_texture()
{
	#ifdef CTM_DEBUG_FAST
		if(binded == 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cTexture - Failed to pad texture! Texture is not binded!\n",true);
			assert(0);
		}
	#endif

	//Check that texture is binded
	if(data != 0)
	{
		data = pad_pixels(data,texwidth,texheight,imgwidth,imgheight);
	}
}

//Get pixel
GLuint texture::get_pixel(UINT32 x, UINT32 y)
{
	#ifdef CTM_DEBUG_SLOW
		if(binded == 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cTexture - Failed to get pixel! Texture is not binded!\n",true);
			assert(0);
		}
	#endif

	#ifdef CTM_DEBUG_SLOW
		if((x > texwidth) || (y > texheight))
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cTexture - Failed to get pixel! Coordinates are out of range!\n",true);
			assert(0);
		}
	#endif

	return data[y*texwidth+x];
}

//Get color
color texture::get_color(UINT32 x, UINT32 y)
{
	#ifdef CTM_DEBUG_SLOW
		if(binded == 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cTexture - Failed to get pixel! Texture is not binded!\n",true);
			assert(0);
		}
	#endif

	#ifdef CTM_DEBUG_SLOW
		if((x > texwidth) || (y > texheight))
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cTexture - Failed to get pixel! Coordinates are out of range!\n",true);
			assert(0);
		}
	#endif

	return pixel_to_color(data[y*texwidth+x]);
}

//Set pixel
void texture::set_pixel(UINT32 x, UINT32 y, GLuint nData)
{
	#ifdef CTM_DEBUG_SLOW
		if(binded == 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cTexture - Failed to set pixel! Texture is not binded!\n",true);
			assert(0);
		}
	#endif

	#ifdef CTM_DEBUG_SLOW
		if((x >= texwidth) || (y >= texheight))
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cTexture - Failed to set pixel! Coordinates are out of range!\n",true);
			assert(0);
		}
	#endif

	data[y*texwidth+x] = nData;
}

//Set pixel with color
void texture::set_color(UINT32 x, UINT32 y, color brush)
{
	#ifdef CTM_DEBUG_SLOW
		if(binded == 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cTexture - Failed to set pixel! Texture is not binded!\n",true);
			assert(0);
		}
	#endif

	//Modify pixel
	set_pixel(x,y,color_to_pixel(brush));
}

//Initialize buffers
void texture::init_buffers()
{
	//Make sure texture is loaded
	if(id != 0 && vboid == 0)
	{
		texvertex vertices[4]; //Make vertex array
		GLuint indices[4] = { 0,1,2,3 }; //Make indice array

		//Make vertex buffer
		glGenBuffers(1,&vboid); //Generate vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER,vboid); //Bind vertex buffer
		glBufferData(GL_ARRAY_BUFFER,sizeof(texvertex)*4,vertices,GL_DYNAMIC_DRAW);

		//Make indice buffer
		glGenBuffers(1,&iboid); //Generate indice buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,iboid); //Bind indice buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLuint)*4,indices,GL_DYNAMIC_DRAW);

		//Unbind buffers
		glBindBuffer(GL_ARRAY_BUFFER,0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	}
}

//Free buffers
void texture::free_buffers()
{
	if(vboid != 0) glDeleteBuffers(1,&vboid);
	vboid = 0;

	if(iboid != 0) glDeleteBuffers(1,&iboid);
	iboid = 0;
}

//Resizes an array of pixels to the lowest power of 2
GLuint *texture::pad_pixels(GLuint *data, GLuint &texwidth, GLuint &texheight, GLuint &imgwidth, GLuint &imgheight)
{
	#ifdef CTM_DEBUG_FAST
		if(data == 0)
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cTexture - Failed to pad pixels! Invalid pointer to data!",true);
			assert(0);
		}
	#endif

	GLuint otexwidth = texwidth; //Store old texture width
	GLuint otexheight = texheight; //Store old texture height
	
	texwidth = lowestpow2(texwidth); //Find lowest power of 2 for width
	texheight = lowestpow2(texheight); //Find lowest power of 2 for height

	//Check that texture needs padding
	if((texwidth != otexwidth) || (texheight != otexheight))
	{
		//Allocate new texture data
		GLuint *newdata = 0;
		if(alloc == 0)
			newdata = new GLuint[texwidth*texheight];
		else
			newdata = (GLuint*)alloc->allocate(sizeof(GLuint)*texwidth*texheight);

		//Copy data
		for(UINT32 count = 0; count < imgheight; ++count)
		{
			memcpy(&newdata[count*texwidth],&data[count*otexwidth],imgwidth*4);
		}
		
		//Deallocate old data
		if(alloc == 0)
			delete[] data;
		else
			alloc->deallocate((void*)data);

		return newdata; //Return pointer to new data
	}
	return data;
}

//Converts a color into an integer pixel
GLuint color_to_pixel(color brush)
{
	GLuint paint = 0; //Integer pixel
	GLubyte *temp = 0; //Channel changer
	temp = (GLubyte*)&paint; //Set channel changer
	temp[0] = (GLubyte)brush.red*255; //Set red
	temp[1] = (GLubyte)brush.green*255; //Set green
	temp[2] = (GLubyte)brush.blue*255; //Set blue
	temp[3] = (GLubyte)brush.alpha*255; //Set alpha
	return paint;
}

//Converts an integer pixel into a color
color pixel_to_color(GLuint pixel)
{
	color brush(0,0,0,0); //Color
	GLubyte *temp = 0; //Channel changer
	temp = (GLubyte*)&pixel; //Set channel changer
	brush.red = (FLOAT32)temp[0]/255; //Set red
	brush.green = (FLOAT32)temp[1]/255; //Set green
	brush.blue = (FLOAT32)temp[2]/255; //Set blue
	brush.alpha = (FLOAT32)temp[3]/255; //Set alpha
	return brush;
}

}