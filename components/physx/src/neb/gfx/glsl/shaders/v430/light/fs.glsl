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

in VS_OUT
{
	dvec4 P;
        dvec3 N;
	dvec2 texcoor;
	dmat4 modelview;
} fs_in;

uniform Light lights[20];
uniform int light_count;
uniform dmat4 view;
uniform Material front;


out vec4 outcolor;

void main(void)
{
	double tau = 6.28318530718;

	// Normalize the incoming N, L and V dvectors
	dvec3 N = normalize(fs_in.N);
	dvec4 P = normalize(fs_in.P);
	dmat4 modelview = fs_in.modelview;
	//dvec3 H = normalize(L + V);
	
	dvec4 color = dvec4(0.0);
	
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
			
			L = light_pos - fs_in.P.xyz;

			double l = length(L);

			L = normalize(L);

			atten = 1.0 / (
					lights[i].atten_const +
					lights[i].atten_linear * l +
					lights[i].atten_quad * l * l);

			if(lights[i].spot_cutoff <= (tau/4.0)) // spotlight?
			{
				double clamped_cos = max(0.0, dot(-L, normalize(light_spot_direction)));
				
				if (clamped_cos < cos(float(lights[i].spot_cutoff))) // outside spotlight cone?
				{
					atten = 0.0;
				}
				else // inside spotlight cone
				{
					atten = atten * pow(float(clamped_cos), float(lights[i].spot_exponent));   
				}
			}
		}
		
		double angle = max(0.0, dot(N,L));
		
		diffuse = atten * lights[i].diffuse * front.diffuse * dvec4(dvec3(angle),1.0);
		
		//diffuse = lights[i].diffuse;
		
		//diffuse.r = angle;

		//if( angle <= 0.0 ) diffuse = front.diffuse;
		//if( atten <= 0.0 ) diffuse = front.diffuse;
		
		
		//diffuse.rgb = N;

		// specular
		if (dot(N,L) < 0.0) // light source behind
		{
			specular = dvec4(0.0, 0.0, 0.0, 0.0);
		}
		else // light source in front
		{
			specular = atten * lights[i].specular * front.specular *
				dvec4(dvec3(pow(float(max(0.0, dot(reflect(-L,N), -P.xyz))), float(front.shininess))),1.0);
		}
		
		color += ambient + diffuse + specular;
		
		//color += front.diffuse;
	}
	
	color += emission;
	//color = front.diffuse;

	outcolor = vec4(color);
}


