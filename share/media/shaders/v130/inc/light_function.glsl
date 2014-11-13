
#define POINT 0
#define SPOT 1
#define DIRECTIONAL 2

#define SHADOW 1u

#include "v130/inc/color.glsl"

float atten;
float light_distance;

void	lf_lights(in vec4 amb, in vec4 dif, in vec4 spc, in float shininess) {

	vec4 diffuse;
	vec4 specular;

	//vec4 pos;
	vec3 light_pos;
	vec3 spot_direction;

	//float shininess = 10.0;
	
	float shadow;
	
	float layer[6];
	vec4 shadow_coor[6];
	
	vec2 sh_texcoor;

	float bias = 0.01;

	float shadow_depth;

	vec3 shadow_dir[6];

	if((uint(flag) & SHADOW) > 0u)
	{
		shadow_dir[0] = vec3( 1, 0, 0);
		shadow_dir[1] = vec3(-1, 0, 0);
		shadow_dir[2] = vec3( 0, 1, 0);
		shadow_dir[3] = vec3( 0,-1, 0);
		shadow_dir[4] = vec3( 0, 0, 1);
		shadow_dir[5] = vec3( 0, 0,-1);

		for(int c = 0; c < 6; c++)
		{
			shadow_dir[c] = mat3(view) * shadow_dir[c];
		}
	}

	for(int i = 0; i < light_count; i++) // for all light sources
	{
		if(light_closed[i] == 0) continue;

		// debug ignore spot
		if(light_type[i] == SPOT) continue;

		// ambient
		color += light_ambient[i] * amb;

		// calculate L vector
		if(light_type[i] == DIRECTIONAL)
		{
			light_pos = mat3(view) * light_position[i];

			L = normalize(light_pos);

			atten = 1.0;
		}
		else // POINT and SPOT
		{
			light_pos = vec3(view * vec4(light_position[i], 1.0));

			L = light_pos - vs_mv_P.xyz;

			light_distance = length(L);

			L = normalize(L);

			atten = 1.0 / (
					light_atten_const[i] +
					light_atten_linear[i] * light_distance +
					light_atten_quad[i] * light_distance * light_distance);

			// debugging
			atten = 1.0;

			// check for very small atten
			if(atten < 0.01) continue;
		}

		// shadow
		shadow = 0.0;

		// manual turn off
		if(false) //if((uint(flag) & SHADOW) > 0u)
		{
			layer[0] = light_shadow_sampler_0[i].x;
			layer[1] = light_shadow_sampler_0[i].y;
			layer[2] = light_shadow_sampler_0[i].z;
			layer[3] = light_shadow_sampler_1[i].x;
			layer[4] = light_shadow_sampler_1[i].y;
			layer[5] = light_shadow_sampler_1[i].z;

			if(layer[0] >= 0.0) {
				// directional or spot?
				shadow_coor[0] = light_shadow_vpb_0[i] * vs_m_P;

				// point?
				if(layer[1] >= 0.0)
				{
					shadow_coor[1] = light_shadow_vpb_1[i] * vs_m_P;
					shadow_coor[2] = light_shadow_vpb_2[i] * vs_m_P;
					shadow_coor[3] = light_shadow_vpb_3[i] * vs_m_P;
					shadow_coor[4] = light_shadow_vpb_4[i] * vs_m_P;
					shadow_coor[5] = light_shadow_vpb_5[i] * vs_m_P;
				}
			}
			for(int c = 0; c < 6; c++)
			{
				if(layer[c] >= 0.0)
				{	
					if(light_type[i] == POINT)
					{
						if(dot(L, shadow_dir[c]) > 0.0) continue;
					}

					vec2 sc = shadow_coor[c].xy / shadow_coor[c].w;

					if(sc.x >= 0.0 && sc.x <= 1.0 && sc.y >= 0.0 && sc.y <= 1.0)
					{

						vec3 texcoord = vec3(sc, layer[c]);

						float fd = (shadow_coor[c].z - bias) / shadow_coor[c].w;

						// shadow depth	

						shadow_depth = texture(shadow_map, texcoord).z;
						if(shadow_depth < fd)
						{
							shadow = 0.7;
							continue;
						}

						//shadow = 1.0 - texture(shadow_map, vec4(texcoord, fd));
						//shadow = texture(shadow_map, vec4(texcoord, fd));

						//if(shadow > 0.1) {
						//	shadow = 0.8;
						//	continue;
						//}
					}
				}
			}
		}




		float angle = max(0.0, dot(N,L));

		// debugging
		if(false) {
		if(light_type[i] == SPOT) {
			spot_direction = mat3(view) * light_spot_direction[i];

			float clamped_cos = max(0.0, dot(-L, normalize(spot_direction)));

			if(clamped_cos < cos(light_spot_cutoff[i])) // outside spotlight cone
			{
				atten = 0.0;
			}
			else // inside spotlight cone
			{
				atten = atten * pow(clamped_cos, light_spot_exponent[i]);   
			}
		}
		}

		diffuse = atten * light_diffuse[i] * dif * vec4(vec3(angle),1.0);

		// specular
		if (dot(N,L) < 0.0) // light source behind
		{
			specular = vec4(0);
		}
		else // light source in front
		{

			specular = atten * light_specular[i] * spc *
				vec4(vec3(pow(max(0.0, dot(reflect(-L,N), -P.xyz)), shininess)),1.0);
		}

		diffuse *= (1.0 - shadow);

		if(shadow > 0.0) specular = vec4(0);

		color += diffuse + specular;
		//color = vec4(vec3(shadow_depth),1);
		//color = vec4(L,1);
		//color = vec4(vec3(shadow),1);
		//color = vec4(dot(L, shadow_dir[0]),dot(L, shadow_dir[1]),0,1);

		//color = uint_to_vec4(255u + (255u << 24u));
	}
}


