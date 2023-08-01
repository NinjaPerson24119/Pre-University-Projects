#ifndef CTM_TEXTURESHEET_H
#define CTM_TEXTURESHEET_H

#include "../Base/Base.h"
#include "../Data/cHeapAllocator.h"
#include "cTexture.h"
#include "../Data/cVector1D.h"
#include "../Math/cRectangle.h"

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
		bool add_clip(rect region); //Inserts a clip region at the end of the texture sheet
		void update_clips(); //Updates vertex/indice buffers
		void draw_clip(float x, float y, unsigned int index); //Draws a clip region
		rect get_clip(unsigned int index); //Returns a clip
		unsigned int get_clipcount() { return clips.get_size(); } //Returns the amount of clip regions
private:
	vector1D<rect> clips; //Clip regions
	unsigned int vbo; //Vertex buffer
	unsigned int *ibo; //Indice buffers
	heapallocator *alloc; //Allocator
};
///////////////////////////

}

#endif