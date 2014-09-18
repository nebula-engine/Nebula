#version 130

//#include "v130/inc/material.glsl"

in vec4		vs_P;

uniform mat4	view;

out float fragmentdepth;

void main(void)
{

	//fragmentdepth = gl_FragCoord.z / gl_FragCoord.w;
	fragmentdepth = gl_FragCoord.z;
	//fragmentdepth = vs_P.z;

}



