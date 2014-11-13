#version 130

#include "v130/inc/color.glsl"
#include "v130/inc/material.glsl"

in vec4		vs_P;
in vec4		vs_m_P;
in vec4		vs_mv_P;
in vec3		vs_N;
in vec3		vs_mv_N;
in vec2		vs_texcoor;
in vec3 	vs_T;
in vec3		vs_B;

uniform sampler2DArray	image;
uniform sampler2D	normal_map;

//uniform sampler2DArrayShadow	shadow_map;
uniform sampler2DArray	shadow_map;
uniform int		flag;

uniform float		hf_min;
uniform float		hf_max;

#include "v130/inc/light.glsl"

uniform mat4 view;


uniform bool has_normal_map;

out vec4 color;

vec4 P;
vec3 N;
vec3 L;

#include "v130/inc/light_function.glsl"

void main(void)
{
	float tau = 6.28318530718;

	P = normalize(vs_mv_P);
	N = vs_mv_N;
	
	color = vec4(0.0);
	
	//vec4 amb, dif, spc;
	
	vec4 brown = vec4(0.5, 0.3, 0, 1);
	vec4 green = vec4(0.2, 0.5, 0, 1);
	vec4 white = vec4(1,1,1,1);
	vec4 black = vec4(0,0,0,1);	
	vec4 blue = vec4(0,0,1,1);

	vec4 dif = cm_linear(scale(vs_P.y, hf_min, hf_max), green, brown);
	//vec4 dif = cm_linear(scale(vs_P.y, hf_min, hf_max), white, black);
	//vec4 dif = cm_linear(scale(vs_P.y, -100.0, 10000.0), red, blue);

	vec4 amb = vec4(0.3,0.3,0.3,1);
	vec4 spc = vec4(0);

	//if(vs_instance_sampler.x >= 0.0) {
	//	vec4 image_color = texture(image, vec3(vs_texcoor, vs_instance_sampler.x));
	//	amb = vs_instance_ambient * image_color;
	//	dif = vs_instance_diffuse * image_color;
	//	spc = vs_instance_specular * image_color;
	//} else {
	//	amb = vs_instance_ambient;
	//	dif = vs_instance_diffuse;
	//	spc = vs_instance_specular;
	//}
	
	if(has_normal_map)
	{	
		vec3 norm_vector = texture(normal_map, vs_texcoor).rgb * 2.0 - 1.0;

		norm_vector = normalize(norm_vector);
		
		//N = normalize(N + (mat3(vs_T, vs_B, vs_N) * norm_vector));
		
		// need proper transformation
		N = norm_vector;
	}
	
	
	lf_lights(amb, dif, spc, 100.0);
	
	//color += vs_instance_emission;
	
	//color = vec4(1,1,1,1);
	//color = dif;
	//color = normal_to_color(vs_mv_N);
	//color = normal_to_color(L);
	//color = normal_to_color(N);
	//color = vec4(vec3(atten),1);
	//color = vec4(vec3(scale(light_distance, 20.0, 80.0)),1);
}


	
