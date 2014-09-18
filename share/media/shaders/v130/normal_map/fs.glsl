#version 130

#include "v130/inc/color.glsl"

in vec3 vs_mv_N;
in vec3 vs_N;
in vec3 vs_P;

out vec4 color;

void main(void)
{
	

	vec3 n = vs_N.xzy;
	
	n.x = -n.x;
	//n.y = -n.y;
	//n.z = -n.z;

	color = vec4((n + 1.0) * 0.5, 1.0);


	// debugging
	float y = scale(vs_P.y,-2.5,2.5);
	//color = vec4(vec3(y), 1);
	//color = cm_linear(y, red, vec4(0,0,1,1));
}



