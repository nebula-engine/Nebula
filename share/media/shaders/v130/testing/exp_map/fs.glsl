#version 330 core

layout (location = 0) out vec4 color;

in int vs_triangle_ID;

void main(void)
{
	color = vec4( (float)vs_triangle_ID/32767.0, 1.0, 1.0, 1.0);
}

