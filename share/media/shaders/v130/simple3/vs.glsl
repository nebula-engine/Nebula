#version 130

#include "v130/inc/color.glsl"

out vec4	vs_color;

uniform mat4 view;
uniform mat4 proj;

in vec3		position;
in uint		color;

void main(void) {

	vs_color = uintARGB8888_to_vec4(color);

	// Calculate the clip-space position of each vertex
	gl_Position = proj * view * vec4(position,1.0);
}


