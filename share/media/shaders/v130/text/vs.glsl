#version 130

in vec4 coor; // 0

out vec2 texcoord;

void main(void)
{
	gl_Position = vec4(coor.xy, 0.0, 1.0);
	texcoord = coor.zw;
}

