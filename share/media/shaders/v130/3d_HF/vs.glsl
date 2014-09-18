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

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;

in vec3		position; // 0
in vec3		normal; // 1
in vec2		texcoor; // 2
in vec3		tangent; // 3
in vec3		binormal; // 4


void main(void) {

	mat4 modelview = view * model;
	
	// Calculate view-space coordinate
	vs_P = vec4(position, 1.0);
	vs_m_P = model * vs_P;
	vs_mv_P = modelview * vs_P;

	// Calculate normal in view-space
	vs_N = normalize(normal);
	vs_mv_N = normalize(mat3(modelview) * normal);

	vs_T = normalize(mat3(modelview) * tangent);
	vs_B = normalize(mat3(modelview) * binormal);

	vs_texcoor = texcoor;


	// Calculate the clip-space position of each vertex
	gl_Position = proj * vs_mv_P;
}


