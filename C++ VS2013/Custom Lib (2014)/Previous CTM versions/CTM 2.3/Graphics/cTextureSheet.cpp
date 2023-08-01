#include "cTextureSheet.h"

namespace ctm
{

//Constructor
texturesheet::texturesheet(heapallocator *iAlloc):
texture(iAlloc),
alloc(iAlloc),
clips(iAlloc),
vbo(0),
ibo(0)
{}

//Copy constructor
texturesheet::texturesheet(texturesheet &rhs):
texture(rhs),
clips(rhs.clips),
vbo(0),
ibo(0)
{
	if(rhs.vbo != 0)
		update_clips();
}

//Destructor
texturesheet::~texturesheet()
{
	free_clips();
}

//Operator =
texturesheet &texturesheet::operator=(texturesheet &rhs)
{
	texture::operator=(rhs);
	clips = rhs.clips;
	vbo = 0;
	ibo = 0;
	if(rhs.vbo != 0)
		update_clips();
	return *this;
}

//Free texture
void texturesheet::free_texture()
{
	free_clips();
	texture::free_texture();
}

//Free clips
void texturesheet::free_clips()
{
	//Delete vertex buffer
	if(vbo != 0)
	{
		glDeleteBuffers(1,&vbo);
		vbo = 0;
	}

	//Delete indice buffer
	if(ibo != 0)
	{
		glDeleteBuffers(clips.get_size(),ibo);

		if(alloc == 0)
			delete[] ibo;
		else
			alloc->deallocate((void*)ibo);

		ibo = 0;
	}

	clips.clear(); //Delete clips
}

//Add clip
bool texturesheet::add_clip(rect region)
{
	#ifdef CTM_DEBUG_SLOW
		if(DEFAULT_DEBUGLOG != 0)
			if(((unsigned int)region.left > get_texwidth()) || (region.left < 0))
			{
				DEFAULT_DEBUGLOG->send("Error: cTextureSheet - Failed to push clip! Region is out of range!\n",false);
				return false;
			}
			else
				if(((unsigned int)region.top > get_texheight()) || (region.left < 0))
				{
					DEFAULT_DEBUGLOG->send("Error: cTextureSheet - Failed to push clip! Region is out of range!\n",false);
					return false;
				}
				else
					if(((unsigned int)region.right > get_texwidth()) || (region.right < 0))
					{
						DEFAULT_DEBUGLOG->send("Error: cTextureSheet - Failed to push clip! Region is out of range!\n",false);
						return false;
					}
					else
						if(((unsigned int)region.bottom > get_texheight()) || (region.bottom < 0))
						{
							DEFAULT_DEBUGLOG->send("Error: cTextureSheet - Failed to push clip! Region is out of range!\n",false);
							return false;
						}
	#endif

	clips.push_back(region);
	return true;
}

//Update clips
void texturesheet::update_clips()
{
	//Check that clips and texture exist
	if((get_id() != 0) && (clips.get_size() != 0))
	{
		//Store amount of clips
		unsigned int clipcount = clips.get_size();

		//Delete existing vertex buffer
		if(vbo != 0)
		{
			glDeleteBuffers(1,&vbo);
			vbo = 0;
		}

		//Allocate vertices
		texvertex *vertices = 0;
		if(alloc != 0)
			vertices = new texvertex[clipcount*4];
		else
			vertices = (texvertex*)alloc->allocate(sizeof(texvertex)*clipcount*4);

		//Delete existing indice buffer
		if(ibo != 0)
		{
			glDeleteBuffers(clips.get_size(),ibo);

			if(alloc != 0)
				delete ibo;
			else
				alloc->deallocate((void*)ibo);

			ibo = 0;
		}

		//Allocate indice buffers
		if(alloc == 0)
			ibo = new unsigned int[clipcount*4];
		else
			ibo = (unsigned int*)alloc->allocate(sizeof(unsigned int)*clipcount*4);

		glGenBuffers(1,&vbo); //Generate vertex buffer id
		glGenBuffers(clips.get_size(),ibo); //Generate indice buffer ids

		GLfloat tw = (GLfloat)get_texwidth(); //Get texture width (Actual)
		GLfloat th = (GLfloat)get_texheight(); //Get texture height (Actual)
		unsigned int clipindices[4] = { 0,0,0,0 }; //Indices

		//Scroll clips
		for(unsigned int count = 0; count < clipcount; ++count)
		{
			//Initialize indices
			clipindices[0] = count*4+0;
			clipindices[1] = count*4+1;
			clipindices[2] = count*4+2;
			clipindices[3] = count*4+3;

			//Initialize vertices
			vertices[clipindices[0]].x = 0;
			vertices[clipindices[0]].y = 0;
			vertices[clipindices[0]].s = clips[count].left/tw;
			vertices[clipindices[0]].t = clips[count].top/th;

			vertices[clipindices[1]].x = clips[count].get_width();
			vertices[clipindices[1]].y = 0;
			vertices[clipindices[1]].s = clips[count].right/tw;
			vertices[clipindices[1]].t = clips[count].top/th;

			vertices[clipindices[2]].x = clips[count].get_width();
			vertices[clipindices[2]].y = clips[count].get_height();
			vertices[clipindices[2]].s = clips[count].right/tw;
			vertices[clipindices[2]].t = clips[count].bottom/th;

			vertices[clipindices[3]].x = 0;
			vertices[clipindices[3]].y = clips[count].get_width();
			vertices[clipindices[3]].s = clips[count].left/tw;
			vertices[clipindices[3]].t = clips[count].bottom/th;

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo[count]); //Bind indice buffer
			glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*4,clipindices,GL_STATIC_DRAW); //Send indice data
		}

		glBindBuffer(GL_ARRAY_BUFFER,vbo); //Bind vertex buffer
		glBufferData(GL_ARRAY_BUFFER,sizeof(texvertex)*clipcount*4,vertices,GL_STATIC_DRAW); //Send vertex data
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0); //Unbind indice buffer
		glBindBuffer(GL_ARRAY_BUFFER,0); //Unbind vertex buffer

		//Deallocate vertices
		if(alloc != 0)
			delete[] vertices;
		else
			alloc->deallocate((void*)vertices);
	}
	else
	{
		#ifdef CTM_DEBUG_FAST
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cTextureSheet - Failed to update buffers!\n",false);
		#endif
	}
}

//Draw clip
void texturesheet::draw_clip(float x, float y, unsigned int index)
{
	#ifdef CTM_DEBUG_SLOW
		if(index >= clips.get_size())
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cTextureSheet - Failed to draw clip! Index is out of range!\n",true);
		}
	#endif

	//Check that vertex data exists
	if(vbo != 0)
	{
		glTranslatef(x,y,0); //Translate to drawing location

		glBindTexture(GL_TEXTURE_2D,get_id()); //Bind texture

		glEnableClientState(GL_VERTEX_ARRAY); //Enable vertex arrays
		glEnableClientState(GL_TEXTURE_COORD_ARRAY); //Enable texture coordinate arrays

		glBindBuffer(GL_ARRAY_BUFFER,vbo); //Bind vertex buffer
		glTexCoordPointer(2,GL_FLOAT,sizeof(texvertex),(GLvoid*)offsetof(texvertex,s)); //Set texture coordinates
		glVertexPointer(2,GL_FLOAT,sizeof(texvertex),(GLvoid*)offsetof(texvertex,x)); //Set vertices

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo[index]); //Bind indice buffer
		glDrawElements(GL_QUADS,4,GL_UNSIGNED_INT,0); //Draw elements

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0); //Unbind indice buffer
		glBindBuffer(GL_ARRAY_BUFFER,0); //Unbind vertex buffer

		glDisableClientState(GL_TEXTURE_COORD_ARRAY); //Disable texture coordinate arrays
		glDisableClientState(GL_VERTEX_ARRAY); //Disable vertex arrays

		glBindTexture(GL_TEXTURE_2D,0); //Unbind texture

		glLoadIdentity(); //Undo transformations
	}
}

//Get clip
rect texturesheet::get_clip(unsigned int index)
{
	#ifdef CTM_DEBUG_SLOW
		if(index >= clips.get_size())
		{
			if(DEFAULT_DEBUGLOG != 0)
				DEFAULT_DEBUGLOG->send("Error: cTextureSheet - Failed to get clip! Index is out of range!\n",true);
		}
	#endif

	return clips[index];
}

}