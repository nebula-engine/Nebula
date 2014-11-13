#version 130

#include "v130/inc/light.glsl"
#include "v130/inc/material.glsl"

in vec4 vs_P;
in vec3 vs_N;
in vec2 vs_texcoor;
in vec3 vs_T;
in vec3 vs_B;


uniform Light_Point		lights_point[20];
uniform Light_Spot		lights_spot[20];
uniform Light_Directional	lights_directional[20];


uniform int light_count_point;
uniform int light_count_spot;
uniform int light_count_directional;

uniform mat4 view;
uniform Material front;

uniform bool has_texture;
uniform bool has_normal_map;

uniform sampler2D texture;
uniform sampler2D normal_map;

out vec4 color;

vec4 P;
vec3 N;
vec3 L;

#include "v130/inc/light_function.glsl"

void main(void)
{
	float tau = 6.28318530718;

	P = normalize(vs_P);
	N = vs_N;
	
	color = vec4(0.0);
	
	vec4 amb, dif, spc;
	
	
	if(has_texture) {
		vec4 texture_color = texture2D(texture, vs_texcoor);
		amb = front.ambient * texture_color;
		dif = front.diffuse * texture_color;
		spc = front.specular * texture_color;
	} else {
		amb = front.ambient;
		dif = front.diffuse;
		spc = front.specular;
	}

	if(has_normal_map) {	
		vec3 norm_vector = texture2D(normal_map, vs_texcoor).xyz;
		N = normalize(N + (mat3(vs_T, vs_B, vs_N) * norm_vector));
	}
	
	
	point(amb, dif, spc);
	spot(amb, dif, spc);
	directional(amb, dif, spc);

	color += front.emission;
}


	
