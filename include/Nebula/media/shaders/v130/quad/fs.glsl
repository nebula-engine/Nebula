#version 430 core

in vec2 texcoord;

uniform vec4 quad_color;

out vec4 color;

void main(void)
{
	color = quad_color;
}


