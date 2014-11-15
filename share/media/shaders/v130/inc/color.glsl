#ifndef COLOR_GLSL
#define COLOR_GLSL

vec4	normal_to_color(vec3 n)
{
	n.x = -n.x;
	//n.y = -n.y;
	//n.z = -n.z;

	return vec4((n + 1.0) * 0.5, 1.0);
}

float	scale(float x, float a, float b)
{
	return (x - a) / (b - a);
}
vec4	cm_linear(float x, vec4 a, vec4 b)
{
	return a * x + b * (1.0 - x);
}

vec4	uintRGBA8888_to_vec4(in uint uc)
{
	float a = float(uc & 255u) / 255.0;
	uc >>= 8u;
	float b = float(uc & 255u) / 255.0;
	uc >>= 8u;
	float g = float(uc & 255u) / 255.0;
	uc >>= 8u;
	float r = float(uc & 255u) / 255.0;
	
	return vec4(r,g,b,a);
}
vec4	uintARGB8888_to_vec4(in uint uc)
{
	float b = float(uc & 255u) / 255.0;
	uc >>= 8u;
	float g = float(uc & 255u) / 255.0;
	uc >>= 8u;
	float r = float(uc & 255u) / 255.0;
	uc >>= 8u;
	float a = float(uc & 255u) / 255.0;
	
	return vec4(r,g,b,a);
}

vec4 red = vec4(1,0,0,1);

#endif

