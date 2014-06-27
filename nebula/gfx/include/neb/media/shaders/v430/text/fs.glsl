#version 430 core

in vec2 texcoord;

uniform sampler2D tex;
uniform vec4 font_color;

out vec4 color;

void main(void)
{
	color = vec4(1.0, 1.0, 1.0, texture2D(tex, texcoord).a) * font_color;
	//color = font_color;
}


