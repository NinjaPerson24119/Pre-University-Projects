#ifndef CTM_PRIMITIVES2D_H
#define CTM_PRIMITIVES2D_H

#include "../External/OpenGL.h"
#include "../Base/Base.h"

//Note that functions defined here use direct drawing. Direct drawing is not supported in modern OpenGL
//Functions that are prefixed with Draw will draw solid shapes while those prefixed with Pencil will draw outlines

namespace ctm
{

void DrawPoint(FLOAT32 x, FLOAT32 y, color brush); //Draws a point
void DrawLine(FLOAT32 x1, FLOAT32 y1, FLOAT32 x2, FLOAT32 y2, color brush); //Draw a line
void DrawBlock(FLOAT32 x, FLOAT32 y, FLOAT32 size, color brush); //Draws a block
void DrawRect(FLOAT32 x, FLOAT32 y, FLOAT32 width, FLOAT32 height, color brush); //Draws a rectangle
void DrawCircle(FLOAT32 x, FLOAT32 y, FLOAT32 radius, INT32 pieces, color brush, FLOAT32 percenttodraw = 1); //Draws a circle
void PencilBlock(FLOAT32 x, FLOAT32 y, FLOAT32 size, color brush); //Draws a block outline
void PencilRect(FLOAT32 x, FLOAT32 y, FLOAT32 width, FLOAT32 height, color brush); //Draws a rectangle outline

}

#endif