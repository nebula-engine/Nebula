#version 130

out float fragmentdepth;

void main(void)
{
	fragmentdepth = gl_FragCoord.z;
}



