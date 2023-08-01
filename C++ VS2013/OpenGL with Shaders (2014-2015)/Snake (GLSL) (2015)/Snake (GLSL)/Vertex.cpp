#include "Vertex.h"

//Constructor
Vertex::Vertex():
x(0.f),
y(0.f),
r(0.f),
g(0.f),
b(0.f),
a(0.f)
{}

Vertex::Vertex(float X, float Y, float R, float G, float B, float A):
x(X),
y(Y),
r(R),
g(G),
b(B),
a(A)
{}

void Vertex::SetVertex(float X, float Y, float R, float G, float B, float A)
{
	x = X;
	y = Y;
	r = R;
	g = G;
	b = B;
	a = A;
}