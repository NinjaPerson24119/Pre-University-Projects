#include "GraphicsAssist.h"

//Quad to Triangles
void QuadToTriangles(float X, float Y, float Width, float Height, Color C, Vertex *Vertices, unsigned int IndiceOffset, unsigned int *Indices)
{
	//Write vertices
	Vertices[0].SetVertex(X, Y + Height, C.r, C.g, C.b, C.a);
	Vertices[1].SetVertex(X + Width, Y + Height, C.r, C.g, C.b, C.a);
	Vertices[2].SetVertex(X + Width, Y, C.r, C.g, C.b, C.a);
	Vertices[3].SetVertex(X, Y, C.r, C.g, C.b, C.a);

	//Write indices
	Indices[0] = IndiceOffset + 0;
	Indices[1] = IndiceOffset + 1;
	Indices[2] = IndiceOffset + 2;
	Indices[3] = IndiceOffset + 0;
	Indices[4] = IndiceOffset + 2;
	Indices[5] = IndiceOffset + 3;
}