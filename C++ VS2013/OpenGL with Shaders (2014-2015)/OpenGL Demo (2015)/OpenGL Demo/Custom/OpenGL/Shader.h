#ifndef CTM_SHADER_H
#define CTM_SHADER_H

#include "../IO/File.h"

#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

namespace ctm
{

//////
//Shader
class Shader
{
	friend class ShaderProgram;
public:
	//Base
		Shader();
		Shader(const char *FileName);
	//Shader
		void Load(const char *FileName);
		void Delete();
private:
	//Inaccessible
		Shader(Shader &Rhs);
		Shader &operator=(Shader &Rhs);
	GLuint id;
};
//////

}

#endif