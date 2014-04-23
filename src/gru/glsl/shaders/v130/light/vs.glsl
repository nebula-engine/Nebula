#version 130

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

out dvec4 vs_P;
out dvec3 vs_N;
out dvec2 vs_texcoor;

uniform dmat4 model;
uniform dmat4 view;
uniform dmat4 proj;

in dvec4 position; // 0
in dvec3 normal; // 1
in dvec2 texcoor; // 2

void main(void)
{
	dmat4 modelview = view * model;
	
	// Calculate view-space coordinate
	vs_P = modelview * position;
	
	// Calculate normal in view-space
	vs_N = normalize(mat3(modelview) * normal);
	
	// texture coordinate
	vs_texcoor = texcoor;
	
	// Calculate the clip-space position of each vertex
	gl_Position = proj * vs_P;
}


