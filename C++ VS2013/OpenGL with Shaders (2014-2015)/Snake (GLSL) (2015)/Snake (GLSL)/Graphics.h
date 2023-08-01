#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Vertex.h"

#include <gl\glew.h>
#include <gl\GL.h>
#include <gl\GLU.h>

//////
//Graphics
class Graphics
{
public:
	//Base
		Graphics();
	//Set
		void Setup(const char *VertexShader, const char *FragmentShader);
		void Cleanup();
		void Draw(Vertex *Vertices, unsigned int VertexBufferSize, unsigned int *Indices, unsigned int IndiceBufferSize);
private:
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
	GLuint program;
};
//////

#endif