#ifndef CTM_SHADERPROGRAM_H
#define CTM_SHADERPROGRAM_H

#include "Shader.h"

#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

namespace ctm
{
	
//////
//Shader Program
class ShaderProgram
{
public:
	//Base
		ShaderProgram();
		ShaderProgram(Shader &VertexShader, Shader &FragmentShader);
		~ShaderProgram();
	//Program
		void Link(Shader &VertexShader, Shader &FragmentShader);
		void Use();
private:
	GLuint id;
};
//////
	
}

#endif