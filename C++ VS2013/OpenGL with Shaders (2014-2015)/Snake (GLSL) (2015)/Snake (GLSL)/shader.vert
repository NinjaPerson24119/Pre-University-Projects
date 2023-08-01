#version 330 core

layout(location = 0) in vec2 vertexPosition_modelspace;
layout(location = 1) in vec4 vertexColor;

out vec4 fragmentColor;

void main()
{
	gl_Position.xy = vertexPosition_modelspace;
	gl_Position.w = 1.0;
	fragmentColor = vertexColor;
}