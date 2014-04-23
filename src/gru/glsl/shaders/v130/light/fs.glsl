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

in dvec4 vs_P;
in dvec3 vs_N;
in dvec2 vs_texcoor;

uniform Light lights[20];
uniform int light_count;
uniform dmat4 view;
uniform Material front;

out dvec4 color;

void main(void)
{
	double tau = 6.28318530718;

	// Normalize the incoming N, L and V dvectors
	dvec3 N = normalize(vs_N);
	dvec4 P = normalize(vs_P);
	
	color = dvec4(0.0);
	
	double atten;
	double shadow;
	dvec4 ambient;
	dvec4 diffuse;
	dvec4 specular;
	dvec4 emission;
	dvec3 light_pos;
	dvec3 light_spot_direction;
	dvec3 L;
	dvec4 shadow_coor;
	dvec4 shadow_coor_w_div;

	// emission
	emission = front.emission;

	for(int i = 0; i < light_count; i++) // for all light sources
	{
		// light
		//light_pos = modelview + lights[i].position;
		light_spot_direction = dmat3(view) * lights[i].spot_direction;
		
		// ambient
		ambient = lights[i].ambient * front.ambient;

		// diffuse
		if(0.0 == lights[i].position.w) // directional light?
		{
			atten = 1.0; // no atten
			
			// rotate to view space
			light_pos = dmat3(view) * lights[i].position.xyz;
			
			
			L = normalize(light_pos);
		}
		else // point light or spotlight (or other kind of light) 
		{
			// translate to view space
			//light_pos = lights[i].position.xyz - view[0].xyz;
			//light_pos = dmat3(view) * light_pos;
			
			light_pos = dvec3( view * lights[i].position );
			
			L = light_pos - vs_P.xyz;

			double l = length(L);

			L = normalize(L);

			atten = 1.0 / (
					lights[i].atten_const +
					lights[i].atten_linear * l +
					lights[i].atten_quad * l * l);

			if(lights[i].spot_cutoff <= (tau/4.0)) // spotlight?
			{
				double clamped_cos = max(0.0, dot(-L, normalize(light_spot_direction)));

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
		
		double angle = max(0.0, dot(N,L));
		
		diffuse = atten * lights[i].diffuse * front.diffuse * dvec4(vec3(angle),1.0);
		
		// specular
		if (dot(N,L) < 0.0) // light source behind
		{
			specular = dvec4(0.0, 0.0, 0.0, 0.0);
		}
		else // light source in front
		{
			specular = atten * lights[i].specular * front.specular *
				dvec4(vec3(pow(max(0.0, dot(reflect(-L,N), -P.xyz)), front.shininess)),1.0);
		}
		
		color += ambient + diffuse + specular;
	}
	
	color += emission;
}


