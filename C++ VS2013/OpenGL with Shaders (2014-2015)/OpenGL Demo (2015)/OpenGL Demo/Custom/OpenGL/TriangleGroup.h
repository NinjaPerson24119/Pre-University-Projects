#ifndef CTM_TRIANGLEGROUP_H
#define CTM_TRIANGLEGROUP_H

#include "OpenGL.h"
#include "ShaderProgram.h"
#include "Material.h"

namespace ctm
{

//////
//Triangle Group
class TriangleGroup
{
public:
	//Base
		TriangleGroup();

private:
	//Data
		ShaderProgram *shaderprogram;
		Material *material;
		unsigned int *indices;
		GLuint ibo;
};
//////

}

#endif