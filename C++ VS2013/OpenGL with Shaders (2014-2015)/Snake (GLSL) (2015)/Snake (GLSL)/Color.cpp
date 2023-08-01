#include "Color.h"

//Constructor
Color::Color():
r(0.f),
b(0.f),
g(0.f),
a(0.f)
{}

Color::Color(float R, float G, float B, float A):
r(R),
g(G),
b(B),
a(A)
{}

//Set Color
void Color::SetColor(float R, float G, float B, float A)
{
	r = R;
	g = G;
	b = B;
	a = A;
}