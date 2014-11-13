#version 130

#include "v130/inc/light.glsl"
#include "v130/inc/material.glsl"

in vec4 vs_P;
in vec3 vs_N;
in vec2 vs_texcoor;

uniform Light_Point		lights_point[20];
uniform Light_Spot		lights_spot[20];
uniform Light_Directional	lights_directional[20];


uniform int light_count_point;
uniform int light_count_spot;
uniform int light_count_directional;

uniform mat4 view;
uniform Material front;

out vec4 color;

vec4 P;
vec3 N;
vec3 L;

#include "v130/inc/light_function.glsl"

void main(void)
{
	float tau = 6.28318530718;

	// Normalize the incoming N, L and V vectors
	N = normalize(vs_N);
	P = normalize(vs_P);
	
	color = vec4(0.0);


	point(front.ambient, front.diffuse, front.specular);
	spot(front.ambient, front.diffuse, front.specular);
	directional(front.ambient, front.diffuse, front.specular);

	color += front.emission;
}


