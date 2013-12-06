#version 430 core

struct Light
{
	vec4 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 spot_direction;
	float spot_cutoff;
	float atten_const;
	float atten_linear;
	float atten_quad;
	float spot_exponent;
	float spot_light_cos_cutoff;
};

struct Material
{
	vec4 diffuse;
	vec4 specular;
	vec4 ambient;
	vec4 emission;
	float shininess;
};

struct VS_OUT
{
	vec4 P;
        vec3 N;
	vec2 texcoor;
};

uniform Light lights[20];
uniform int light_count;

uniform Material front;

in VS_OUT fs_in;

out vec4 color;

void main(void)
{
	float tau = 6.28318530718;

	// Normalize the incoming N, L and V vectors
	vec3 N = normalize(fs_in.N);
	vec4 P = normalize(fs_in.P);
	//vec3 H = normalize(L + V);
	
	color = vec4(0.0);
	
	float atten;
	float shadow;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 emission;
	vec3 L;
	vec4 shadow_coor;
	vec4 shadow_coor_w_div;

	// emission
	emission = front.emission;


	for (int i = 0; i < light_count; i++) // for all light sources
	{
		// ambient
		ambient = lights[i].ambient * front.ambient;

		// diffuse
		if (0.0 == lights[i].position.w) // directional light?
		{
			atten = 1.0; // no atten
			L = normalize(vec3(lights[i].position));
		} 
		else // point light or spotlight (or other kind of light) 
		{
			L = vec3(lights[i].position - fs_in.P);

			float l = length(L);

			L = normalize(L);

			atten = 1.0 / (
					lights[i].atten_const +
					lights[i].atten_linear * l +
					lights[i].atten_quad * l * l);

			if(lights[i].spot_cutoff <= (tau/4.0)) // spotlight?
			{
				float clamped_cos = max(0.0, dot(-L, normalize(lights[i].spot_direction)));

				if (clamped_cos < cos(lights[i].spot_cutoff)) // outside spotlight cone?
				{
					atten = 0.0;
				}
				else // inside spotlight cone
				{
					atten = atten * pow(clamped_cos, lights[i].spot_exponent);   
				}
			}
		}

		diffuse = atten * lights[i].diffuse * front.diffuse * vec4(vec3(max(0.0, dot(N,L))),1.0);

		// specular
		if (dot(N,L) < 0.0) // light source behind
		{
			specular = vec4(0.0, 0.0, 0.0, 0.0);
		}
		else // light source in front
		{
			specular = atten * lights[i].specular * front.specular *
				vec4(vec3(pow(max(0.0, dot(reflect(-L,N), -P.xyz)), front.shininess)),1.0);
		}

		color += ambient + diffuse + specular;
	}
	
	color += emission;
	color = front.diffuse;
}


