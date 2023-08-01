#ifndef CTM_SHADER_H
#define CTM_SHADER_H

#include <Custom/Memory/File.h>
#include <Custom/External/OpenGL.h>

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
		Shader(File &Source);
	//Shader
		void Load(File &Source);
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