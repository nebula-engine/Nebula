#version 430 core

struct Light
{
	dvec4 position;
	dvec4 ambient;
	dvec4 diffuse;
	dvec4 specular;
	dvec3 spot_direction;
	double spot_cutoff;
	double atten_const;
	double atten_linear;
	double atten_quad;
	double spot_exponent;
	double spot_light_cos_cutoff;
};

struct Material
{
	dvec4 diffuse;
	dvec4 specular;
	dvec4 ambient;
	dvec4 emission;
	double shininess;
};

out VS_OUT
{
	dvec4 P;
	dvec3 N;
	dvec2 texcoor;
} vs_out;

uniform dmat4 model;
uniform dmat4 view;
uniform dmat4 proj;

layout (location = 0) in dvec4 position;
layout (location = 1) in dvec3 normal;
layout (location = 2) in dvec2 texcoor;

void main(void)
{
	dmat4 modelview = view * model;
	
	// Calculate view-space coordinate
	vs_out.P = modelview * position;
	
	// Calculate normal in view-space
	vs_out.N = normalize(dmat3(modelview) * normal);
	
	// texture coordinate
	vs_out.texcoor = texcoor;
	
	// Calculate the clip-space position of each vertex
	gl_Position = vec4(proj * vs_out.P);
}


