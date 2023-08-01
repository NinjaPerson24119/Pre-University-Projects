#include "Shader.h"
#include <string>
#include <stdexcept>

namespace ctm
{

//Constructor
Shader::Shader():
id(0)
{}

Shader::Shader(const char *FileName):
id(0)
{
	Load(FileName);
}

//Load
void Shader::Load(const char *FileName)
{
	if(id != 0)
		throw std::runtime_error("Shader - Failed to load shader! Shader has already been loaded!\n");

	//Create shader object
	id = glCreateShader(GL_VERTEX_SHADER);

	//Load shader file into string
	File f(FileName, File::FileMode::READ);
	char *source = new char[(unsigned int)f.Size()];
	GLint sourcelength = (GLint)f.Size();
	f.Read(source, sourcelength);
	f.Close();

	//Compile shader
	glShaderSource(id, 0, &source, &sourcelength);
	glCompileShader(id);

	//Delete source
	delete[] source;

	//Check for errors
	GLint result;
	GLint loglength;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &loglength);

	if(result != GL_TRUE)
	{
		char *log = new char[loglength];
		glGetShaderInfoLog(id, loglength, 0, log);
		std::runtime_error error(std::string("Shader - Shader has failed to compile! ") + log);
		delete[] log;
		throw error;
	}
}

//Delete
void Shader::Delete()
{
	if(id == 0)
		throw std::runtime_error("Shader - Failed to delete shader! Shader has not been loaded!");

	glDeleteShader(id);
	id = 0;
}

}