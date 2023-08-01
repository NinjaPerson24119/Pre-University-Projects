#ifndef GRAPHICSASSIST_H
#define GRAPHICSASSIST_H

#include "Color.h"
#include "Vertex.h"

void QuadToTriangles(float X, float Y, float Width, float Height, Color C, Vertex *Vertices, unsigned int IndiceOffset, unsigned int *Indices);

#endif