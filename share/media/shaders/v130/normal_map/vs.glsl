// render the fragment normals as rgb color
// for use in generating normal maps

#version 130

out vec3	vs_mv_N;
out vec3	vs_N;
out vec3	vs_P;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;

in vec3		position;
in vec3		normal;

void main(void)
{
	mat4 mvp = proj * view * model;
	mat4 mv = view * model;
	
	// Calculate view-space coordinate

	vs_N = normalize(normal);
	vs_mv_N = normalize(mat3(mv) * normal);

	vs_P = position;

	// Calculate the clip-space position of each vertex
	gl_Position = mvp * vec4(position,1.0);
}


