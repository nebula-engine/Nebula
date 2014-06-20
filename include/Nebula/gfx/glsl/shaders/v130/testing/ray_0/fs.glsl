#version 330 core

struct ray
{
vec3 origin;
vec3 direction;
}

struct sphere
{
vec3 center;
float radius;
vec4 color;
}

float intersect_ray_plane(ray R, vec4 P, out vec3 hitpos, out vec3 normal)
{
	vec3 O = R.origin;
	vec3 D = R.direction;
	vec3 N = P.xyz;
	float d = P.w;
	
	float denom = dot(N,D);
	
	if(denom == 0.0) return 0.0;
	
	float t = -(d + dot(O,N)) / denom;
	
	if(t < 0.0) return 0.0;
	
	hitpos = O + t * D;
	normal = N;
	
	return t;
}
float intersect_ray_sphere(ray R, sphere S, out vec3 hitpos, out vec3 normal)
{
	vec3 v = R.origin - S.center;
	float B = 2.0 * dot(R.direction, v);
	float C = dot(v,v) - S.radius * S.radius;
	float B2 = B * B;
	
	float f = B2 - 4.0 * C;
	
	if(f < 0.0) return 0.0;
	
	float t0 = -B + sqrt(f);
	float t1 = -B - sqrt(f);
	float t = min(max(t0, 0.0), max(t1, 0.0)) * 0.5;
	
	if(t == 0.0) return 0.0;
	
	hitpos = R.origin + t * R.direction;
	normal = normalize(hitpos - S.center);
	
	return t;
}

uniform SPHERES
{
	sphere S[128];
}
uniform PLANES
{
	vec4 P[128];
}

// texture with ray origin and direction
uniform sampler2D tex_origin;
uniform sampler2D tex_direction;

out vec4 color;

// using alpha as reflectivity, no transparency at this point

void recurse(ray R, out vec4 color, int remaining_trace)
{
	float min_t = 1000000.0f;
	float t;

	ret_color = vec4(0.0);
	object_type = -1;
	
	for(int i = 0; i < num_spheres; ++i)
	{
		// find intersection point
		t = intersect_ray_sphere(R, S[i], hitpos, normal);

		// if there is an intersection
		if(t != 0.0)
		{
			// and that intersection is less than out current closest
			if(t < min_t)
			{
				// record it
				min_t = t;
				hit_position = hitpos;
				hit_normal = normal;
				sphere_index = i;
				object_type = 0;

				// new ray
				R.origin = hit_position;
				R.direction = Reflect(R.direction,hit_normal);
			}
		}
	}

	for(int i = 0; i < num_planes; ++i)
	{
		// find intersection point
		t = intersect_ray_plane(R, P[i], hitpos, normal);

		// if there is an intersection
		if(t != 0.0)
		{
			// and that intersection is less than out current closest
			if(t < min_t)
			{
				// record it
				min_t = t;
				hit_position = hitpos;
				hit_normal = normal;
				plane_index = i;
				object_type = 1;

				// new ray
				R.origin = hit_position;
				R.direction = Reflect(R.direction,hit_normal);

			}
		}
	}

	// return if ray didnt intersect anything
	if(object_type == -1) return;
	
	vec4 o(0.0);
	
	// fire another ray
	// in future versions, fire multiple rays for objects with reflection and transparency
	if(remaining_trace > 0)	recurse(R, o, remaining_trace-1);
	
	
	// get color for object hit by this ray
	vec4 c;
	if(object_type == 0)
	{
		c = S[sphere_index].color;
	}
	else if(object_type == 1)
	{
		c = P[plane_index].color;
	}
	
	// apply lighting to color
	
	
	// blend with color returned by fired ray
	ret_color.rgb = c.rgb * c.a + o * (1 - c.a);
	
}
void main(void)
{
	ray R;

	R.origin = texelFetch(tex_origin, ivec2(gl_FragCoord.xy), 0).xyz;
	R.direction = texelFetch(tex_direction, ivec2(gl_FragCoord.xy), 0).xyz;

	recurse(R, color, num_trace);
}



