#include <Custom/Graphics/ShaderProgram.h>
#include <stdexcept>
#include <string>

namespace ctm
{

//Contructor
ShaderProgram::ShaderProgram():
id(0)
{}

ShaderProgram::ShaderProgram(Shader &VertexShader, Shader &FragmentShader):
id(0)
{
	Link(VertexShader, FragmentShader);
}

//Destructor
ShaderProgram::~ShaderProgram()
{
	if(id != 0)
		glDeleteProgram(id);
}

//Link
void ShaderProgram::Link(Shader &VertexShader, Shader &FragmentShader)
{
	if(id != 0)
		throw std::runtime_error("ShaderProgram - Failed to link program! Program has already been linked!");
	
	//Create program
	id = glCreateProgram();
	
	//Attach shaders to program
	glAttachShader(id, VertexShader.id);
	glAttachShader(id, FragmentShader.id);
	
	//Link
	glLinkProgram(id);
	
	//Detach shaders
	glDetachShader(id, VertexShader.id);
	glDetachShader(id, FragmentShader.id);
	
	//Check for errors
	GLint result = 0;
	glGetProgramiv(id, GL_LINK_STATUS, &result);
	
	if(result != GL_TRUE)
	{
		GLint loglength = 0;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &loglength);
		char *log = new char[loglength];
		glGetProgramInfoLog(id, loglength, 0, log);
		std::runtime_error error(std::string("ShaderProgram - Failed to link program!") + log);
		delete[] log;
		throw error;
	}
}

//Use
void ShaderProgram::Use()
{
	glUseProgram(id);
	
	//Check for errors
	GLenum error = glGetError();
	if(error != GL_NO_ERROR)
		throw std::runtime_error(std::string("ShaderProgram - Failed to set program as current!") + (char*)gluErrorString(error));
}

}