#ifndef CTM_VERTEX_H
#define CTM_VERTEX_H

namespace ctm
{

//////
//Vertex
class Vertex
{
public:
	//Base
		Vertex();
		Vertex(float X, float Y, float R, float G, float B, float A = 1.f);
	//Set
		void SetVertex(float X, float Y, float R, float G, float B, float A = 1.f);
	//Data
		float x, y;
		float r, g, b, a;
};
//////

}

#endif