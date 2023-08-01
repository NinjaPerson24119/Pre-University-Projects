#ifndef CTM_PRIMITIVES2D_H
#define CTM_PRIMITIVES2D_H

#include "../Base/Base.h"
#include "cColor.h"

//Note that functions defined here use direct drawing. Direct drawing is not supported in modern OpenGL
//Functions that are prefixed with Draw will draw solid shapes while those prefixed with Pencil will draw outlines

namespace ctm
{

void DrawPoint(float x, float y, color brush); //Draws a point
void DrawLine(float x1, float y1, float x2, float y2, color brush); //Draw a line
void DrawBlock(float x, float y, float size, color brush); //Draws a block
void DrawRect(float x, float y, float width, float height, color brush); //Draws a rectangle
void DrawCircle(float x, float y, float radius, int pieces, color brush, float percenttodraw = 1); //Draws a circle
void PencilBlock(float x, float y, float size, color brush); //Draws a block outline
void PencilRect(float x, float y, float width, float height, color brush); //Draws a rectangle outline

}

#endif