#version 130

out vec4	vs_P;

uniform mat4 view;
uniform mat4 proj;

in vec3		position;
in vec4		instance_model_0;
in vec4		instance_model_1;
in vec4		instance_model_2;
in vec4		instance_model_3;

void main(void) {

	mat4 model = mat4(
			instance_model_0,
			instance_model_1,
			instance_model_2,
			instance_model_3);

	mat4 modelview = view * model;
	
	// Calculate view-space coordinate

	vs_P = modelview * vec4(position,1.0);

	// Calculate the clip-space position of each vertex
	gl_Position = proj * vs_P;
}


