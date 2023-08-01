#include "Graphics.h"
#include "File.h"

//Constructor
Graphics::Graphics():
vao(0),
vbo(0),
ibo(0),
program(0)
{}

//Setup
void Graphics::Setup(const char *VertexShader, const char *FragmentShader)
{
	//Generate objects
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	//Bind VAO and VBO
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//Set position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	//Set color attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 2));

	//Create shaders
	GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
	GLint vslength = 0;
	GLint fslength = 0;
	GLint result = 0;
	int loglength = 0;
	char *log = nullptr;

	//Load vertex shader into string
	ctm::File shaderfile(VertexShader, ctm::File::FileMode::READ);
	char *vsstring = new char[shaderfile.size()];
	shaderfile.read(vsstring, shaderfile.size());
	vslength = shaderfile.size();
	shaderfile.close();
	
	//Load fragment shader into string
	shaderfile.open(FragmentShader, ctm::File::FileMode::READ);
	char *fsstring = new char[shaderfile.size()];
	shaderfile.read(fsstring, shaderfile.size());
	fslength = shaderfile.size();
	shaderfile.close();

	//Compile vertex shader
	glShaderSource(vertexshader, 1, &vsstring, &vslength);
	glCompileShader(vertexshader);
	delete[] vsstring;

	//Check for errors
	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &result);

	if(result == GL_FALSE)
	{
		glGetShaderiv(vertexshader, GL_INFO_LOG_LENGTH, &loglength);
		log = new char[loglength];
		glGetShaderInfoLog(vertexshader, loglength, 0, log);	
		throw std::runtime_error(log);
	}

	//Compile fragment shader
	glShaderSource(fragmentshader, 1, &fsstring, &fslength);
	glCompileShader(fragmentshader);
	delete[] fsstring;

	//Check for errors
	glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &result);

	if(result == GL_FALSE)
	{
		glGetShaderiv(fragmentshader, GL_INFO_LOG_LENGTH, &loglength);
		log = new char[loglength];
		glGetShaderInfoLog(fragmentshader, loglength, 0, log);
		throw std::runtime_error(log);
	}

	//Link the program
	program = glCreateProgram();
	glAttachShader(program, vertexshader);
	glAttachShader(program, fragmentshader);
	glLinkProgram(program);

	//Check for errors
	glGetProgramiv(program, GL_LINK_STATUS, &result);

	if(result == GL_FALSE)
	{
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &loglength);
		log = new char[loglength];
		glGetProgramInfoLog(program, loglength, 0, log);
		throw std::runtime_error(log);
	}

	//Delete shaders
	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);

	//Set shader program
	glUseProgram(program);

	GLenum error = glGetError();
	if(error != GL_NO_ERROR)
		throw std::runtime_error("Graphics - Setup failed!\n");
}

//Clean up
void Graphics::Cleanup()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	glDeleteProgram(program);
}

//Draw
void Graphics::Draw(Vertex *Vertices, unsigned int VertexBufferLength, unsigned int *Indices, unsigned int IndiceBufferLength)
{
	//Bind vertex array
	glBindVertexArray(vao);

	//Send vertex data
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, VertexBufferLength, Vertices, GL_DYNAMIC_DRAW);

	//Send indice data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndiceBufferLength, Indices, GL_DYNAMIC_DRAW);

	//Draw
	//glDrawArrays(GL_TRIANGLES, 0, VertexBufferLength / 3);
	//glDrawElements(GL_TRIANGLES, IndiceBufferLength / sizeof(unsigned int), GL_UNSIGNED_INT, (void*)0);
}
