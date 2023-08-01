#ifndef CTM_TEXTURESHEET_H
#define CTM_TEXTURESHEET_H

#include "../Base/Base.h"
#include "../Data/cHeapAllocator.h"
#include "cTexture.h"
#include "../Data/cVector1D.h"

namespace ctm
{

///////////////////////////
//Texture sheet class
class texturesheet : public texture
{
public:
	//System
		texturesheet(heapallocator *iAlloc);
		texturesheet(texturesheet &rhs);
		~texturesheet();
		texturesheet &operator=(texturesheet &rhs);
		void free_texture(); //Deletes any existing texture data
		void free_clips(); //Resets the clip array and vertex/indice buffers
		BOOL8 add_clip(rect region); //Inserts a clip region at the end of the texture sheet
		void update_clips(); //Updates vertex/indice buffers
		void draw_clip(FLOAT32 x, FLOAT32 y, UINT32 index); //Draws a clip region
		rect get_clip(UINT32 index); //Returns a clip
		UINT32 get_clipcount() { return clips.get_size(); } //Returns the amount of clip regions
private:
	vector1D<rect> clips; //Clip regions
	GLuint vbo; //Vertex buffer
	GLuint *ibo; //Indice buffers
	heapallocator *alloc; //Allocator
};
///////////////////////////

}

#endif