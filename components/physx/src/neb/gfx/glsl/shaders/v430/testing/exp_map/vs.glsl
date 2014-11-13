#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in int triangle_ID;

uniform mat4 model;
uniform mat4 view;

// explosion map sphere
uniform vec3 center;
uniform float radius;

out int vs_triangle_ID;

void calc(in float b, in float c, in float cosC, out float a)
{
	float t0 = b * cosC
	float t1 = sqrt(c*c - b*b*(1 - cosC*cosC));

	float a0 = t0 + t1;
	float a1 = t0 - t1;
	
	if( a0 > 0 )
	{
		a = a0;
	}
	else
	{
		a = a1;
	}
}

void main(void)
{
	mat4 modelview = view * model;
	
        // Calculate view-space coordinate
        vec4 P = modelview * position;
	
        // Calculate normal in view-space
        vec3 N = normalize(mat3(modelview) * normal);
	
	
	vec3 B = center - P;
	float b = length(B);
	
	vec3 R = normalize(reflect(P,N));
	
	float cosC = dot(B,R) / b;
	
	float a;
	calc(b, radius, cosC, a);
	
	vec3 A = a * R;
	
	float s = radius/2 * ( 1 + ( A.x / sqrt( 2*(A.z+1) ) ) );
	float t = radius/2 * ( 1 + ( A.y / sqrt( 2*(A.z+1) ) ) );
	
        gl_Position = vec3(s, t, -1.0);
	
	vs_triangle_ID = triangle_ID;
}



