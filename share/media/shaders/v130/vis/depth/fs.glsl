#version 130
#define TAU 6.28

in vec4		vs_P;

uniform mat4	view;

out vec4 color;



void		sinecolor(in float f, inout vec4 c)
{
	c.r = 0.5 * sin(TAU / 4.0 * f) + 0.5;
	c.g = 0.5 * sin(TAU / 2.0 * f) + 0.5;
	c.b = 0.5 * sin(TAU / 1.0 * f) + 0.5;
	c.a = 1.0;
}

float near = 0;
float far = 100;

float map(float z)
{
	if(z < near) z = near;
	if(z > far) z = far;

	float f = (z - near) / (far - near);

	return f;
}

vec4		gray(float f)
{
	return vec4(f,f,f,1);
}

void main(void)
{
	
	
	//color = vec4(gl_FragCoord.zzz, 1);
	//sinecolor(vs_P.z, color);
	//sinecolor(gl_FragCoord.z, color);
	//sinecolor(gl_FragCoord.z / gl_FragCoord.w, color);

	color = gray(map(-vs_P.z));

}



