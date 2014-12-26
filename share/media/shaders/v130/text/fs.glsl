#version 130

in vec2 texcoord;

uniform sampler2D tex;
uniform vec4 font_color;

vec4 background_color = vec4(1.0,1.0,1.0,1.0);

out vec4 color;

void main(void)
{
	float a = texture2D(tex, texcoord).a;
	color = vec4(1.0, 1.0, 1.0, a) * font_color;
	color += (1 - a) * background_color;
	//color = font_color;
}


