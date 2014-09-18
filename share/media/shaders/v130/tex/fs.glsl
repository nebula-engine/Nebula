#version 130

in vec2 texcoord;

//uniform sampler2D tex;
uniform sampler2DArray tex;

out vec4 color;

void main(void)
{
	//color = vec4(1.0, 1.0, 1.0, texture2D(tex, texcoord).a) * font_color;
	//color = texture2D(tex, texcoord * vec2(0.5));
	color = texture(tex, vec3(texcoord, 4.0));
}



