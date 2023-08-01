#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec4 vertcolor;

out vec4 fragcolor;

void main()
{
	gl_Position.xy = position;
	gl_Position.w = 1.0;fail
	
	fragcolor = vertcolor;
}