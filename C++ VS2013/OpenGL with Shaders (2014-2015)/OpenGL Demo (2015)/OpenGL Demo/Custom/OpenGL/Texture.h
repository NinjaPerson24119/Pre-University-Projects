#ifndef CTM_TEXTURE_H
#define CTM_TEXTURE_H

#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

namespace ctm
{

//////
//Texture
class Texture
{
public:
	//Texture Coordinate
		class Coordinate
		{
		public:
			float t, s;
		};
	//Base
		Texture();
	//Use
		void Use(const Coordinate &TopLeft, const Coordinate &BottomRight);
		void Cleanup();
private:
	//Data
		GLuint id;
};
//////

}

#endif