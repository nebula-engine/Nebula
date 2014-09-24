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

in VS_OUT
{
	vec4 P;
        vec3 N;
	vec2 texcoor;
} fs_in;

uniform Light lights[20];
uniform sampler2D shadow_map[20];
uniform mat4 matrix_shadow[20];

uniform int light_count;
uniform mat4 view;
uniform Material front;

out vec4 color;

void main(void)
{
	float tau = 6.28318530718;

	// Normalize the incoming N, L and V vectors
	vec3 N = normalize(fs_in.N);
	vec4 P = normalize(fs_in.P);
	mat4 modelview = fs_in.modelview;
	//vec3 H = normalize(L + V);
	
	color = vec4(0.0);
	
	float atten;
	float shadow;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 emission;
	vec3 light_pos;
	vec3 light_spot_direction;
	vec3 L;
	vec4 shadow_coor;
	vec4 shadow_coor_w_div;

	// emission
	emission = front.emission;

	for(int i = 0; i < light_count; i++) // for all light sources
	{
		// shadow
		shadow_coor = matrix_shadow[i] * fs_in.P;

		shadow_coor_w_div = shadow_coor / shadow_coor.w;

		// used to lower moire pattern and self-shadowing
		shadow_coor_w_div += 0.0005;

		float dist_from_light = texture2D(shadow_map[i], shadow_coor_w_div.st).z;


		if((shadow_coor.w < 0.0) || (dist_from_light > shadow_coor_w_div.z)) // not in shadow?
		{
			shadow = 0.0;
		}
		else // in shadow
		{
			shadow = 1.0;
		}


		// light
		light_spot_direction = mat3(view) * lights[i].spot_direction;

		// ambient
		ambient = lights[i].ambient * front.ambient;


		specular = vec4(0.0, 0.0, 0.0, 0.0);
		deffuse = vec4(0.0, 0.0, 0.0, 0.0);
		if(shadow == 0.0)
		{
			// diffuse
			if(0.0 == lights[i].position.w) // directional light?
			{
				atten = 1.0; // no atten

				// rotate to view space
				light_pos = mat3(view) * lights[i].position.xyz;


				L = normalize(light_pos);
			}
			else // point light or spotlight (or other kind of light) 
			{
				// translate to view space
				light_pos = vec3( view * lights[i].position );

				L = light_pos - fs_in.P.xyz;

				float l = length(L);

				L = normalize(L);

				atten = 1.0 / (
						lights[i].atten_const +
						lights[i].atten_linear * l +
						lights[i].atten_quad * l * l);

				if(lights[i].spot_cutoff <= (tau/4.0)) // spotlight?
				{
					float clamped_cos = max(0.0, dot(-L, normalize(light_spot_direction)));

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

			float angle = max(0.0, dot(N,L));

			diffuse = atten * lights[i].diffuse * front.diffuse * vec4(vec3(angle),1.0);

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
		}

		color += ambient + diffuse + specular;
	}

	color += emission;
}


