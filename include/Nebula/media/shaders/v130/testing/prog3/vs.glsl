#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

out VS_OUT
{
        vec3 N;
        vec3 L;
        vec3 V;
} vs_out;

uniform vec3 light_pos = vec3(10.0, 10.0, 5.0);

void main(void)
{
	mat4 modelview = view_matrix * model_matrix;

        // Calculate view-space coordinate
        vec4 P = modelview * position;

        // Calculate normal in view-space
        vs_out.N = mat3(modelview) * normal;

        // Calculate light vector
        vs_out.L = light_pos - P.xyz;

        // Calculate view vector
        vs_out.V = -P.xyz;

        // Calculate the clip-space position of each vertex
        gl_Position = proj_matrix * P;
}



