#version 330 core

in vec4 fragmentColor;

out vec4 color;

void main()
{
	gl_FragColor = fragmentColor;
	color = fragmentColor;
}