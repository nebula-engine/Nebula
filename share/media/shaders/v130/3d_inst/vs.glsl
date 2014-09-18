#version 130

#include "v130/inc/color.glsl"

out vec4	vs_P;
out vec4	vs_m_P;
out vec4	vs_mv_P;

out vec3	vs_N;
out vec3	vs_mv_N;

out vec2	vs_texcoor;
out vec3	vs_T;
out vec3	vs_B;
out vec4	vs_instance_sampler;
out vec4	vs_instance_diffuse;
out vec4	vs_instance_ambient;
out vec4	vs_instance_specular;
out vec4	vs_instance_emission;
out float	vs_instance_shininess;

uniform mat4 view;
uniform mat4 proj;

in vec3		position; // 0
in vec3		normal; // 1
in vec2		texcoor; // 2
in vec3		tangent; // 3
in vec3		binormal; // 4
in vec4		instance_model_0;
in vec4		instance_model_1;
in vec4		instance_model_2;
in vec4		instance_model_3;
in vec4		instance_sampler;
in uint		instance_diffuse;
in vec4		instance_ambient;
in vec4		instance_specular;
in vec4		instance_emission;
in float	instance_shininess;

void main(void) {

	mat4 model = mat4(
			instance_model_0,
			instance_model_1,
			instance_model_2,
			instance_model_3);

	mat4 modelview = view * model;
	
	// Calculate view-space coordinate
	vs_P = vec4(position,1.0);
	vs_m_P = model * vec4(position,1.0);
	vs_mv_P = modelview * vec4(position,1.0);

	// Calculate normal in view-space
	vs_N = normalize(normal);
	vs_mv_N = normalize(mat3(modelview) * normal);

	vs_T = normalize(mat3(modelview) * tangent);
	vs_B = normalize(mat3(modelview) * binormal);

	vs_texcoor = texcoor;

	vs_instance_sampler = instance_sampler;

	vs_instance_diffuse = uintRGBA8888_to_vec4(instance_diffuse);
	vs_instance_ambient = instance_ambient;
	vs_instance_specular = instance_specular;
	vs_instance_emission = instance_emission;
	vs_instance_shininess = instance_shininess;

	// Calculate the clip-space position of each vertex
	gl_Position = proj * vs_mv_P;
}


