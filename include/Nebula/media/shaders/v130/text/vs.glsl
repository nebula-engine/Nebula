#version 130

in vec4 coord; // 0

out vec2 texcoord;

void main(void)
{
	gl_Position = vec4(coord.xy, 0.0, 1.0);
	texcoord = coord.zw;
}

