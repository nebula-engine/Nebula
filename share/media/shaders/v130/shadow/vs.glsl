#version 130

out vec4	vs_P;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;

in vec3		position;

void main(void) {

	mat4 modelview = view * model;
	
	// Calculate view-space coordinate

	vs_P = modelview * vec4(position,1.0);

	// Calculate the clip-space position of each vertex
	gl_Position = proj * vs_P;
}


