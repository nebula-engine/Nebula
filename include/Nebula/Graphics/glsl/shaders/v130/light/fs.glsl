#version 130

struct Light_Point
{
	vec3 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float atten_const;
	float atten_linear;
	float atten_quad;
};

struct Light_Spot
{
	vec3 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 spot_direction;
	float spot_cutoff;
	float spot_exponent;
	float spot_light_cos_cutoff;
	float atten_const;
	float atten_linear;
	float atten_quad;
};

struct Light_Directional
{
	vec3 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

struct Material
{
	vec4 diffuse;
	vec4 specular;
	vec4 ambient;
	vec4 emission;
	float shininess;
};

in vec4 vs_P;
in vec3 vs_N;
in vec2 vs_texcoor;

uniform Light_Point		lights_point[20];
uniform Light_Spot		lights_spot[20];
uniform Light_Directional	lights_directional[20];


uniform int light_count_point;
uniform int light_count_spot;
uniform int light_count_directional;

uniform mat4 view;
uniform Material front;

out vec4 color;

void main(void)
{
	float tau = 6.28318530718;

	// Normalize the incoming N, L and V vectors
	vec3 N = normalize(vs_N);
	vec4 P = normalize(vs_P);
	
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

	for(int i = 0; i < light_count_point; i++) // for all light sources
	{
		// ambient
		ambient = lights_point[i].ambient * front.ambient;

		// diffuse
		// translate to view space
		//light_pos = lights[i].position.xyz - view[0].xyz;
		//light_pos = mat3(view) * light_pos;

		light_pos = vec3( view * lights_point[i].position );

		L = light_pos - vs_P.xyz;

		float l = length(L);

		L = normalize(L);

		atten = 1.0 / (
				lights_point[i].atten_const +
				lights_point[i].atten_linear * l +
				lights_point[i].atten_quad * l * l);


		float angle = max(0.0, dot(N,L));

		diffuse = atten * lights_point[i].diffuse * front.diffuse * vec4(vec3(angle),1.0);

		// specular
		if (dot(N,L) < 0.0) // light source behind
		{
			specular = vec4(0.0, 0.0, 0.0, 0.0);
		}
		else // light source in front
		{
			specular = atten * lights_point[i].specular * front.specular *
				vec4(vec3(pow(max(0.0, dot(reflect(-L,N), -P.xyz)), front.shininess)),1.0);
		}

		color += ambient + diffuse + specular;
	}
	for(int i = 0; i < light_count_spot; i++) // for all light sources
	{
		// light
		//light_pos = modelview + lights[i].position;
		light_spot_direction = mat3(view) * lights_spot[i].spot_direction;

		// ambient
		ambient = lights_spot[i].ambient * front.ambient;

		// diffuse
		// translate to view space
		//light_pos = lights[i].position.xyz - view[0].xyz;
		//light_pos = mat3(view) * light_pos;

		light_pos = vec3( view * lights_spot[i].position );

		L = light_pos - vs_P.xyz;

		float l = length(L);

		L = normalize(L);

		atten = 1.0 / (
				lights_spot[i].atten_const +
				lights_spot[i].atten_linear * l +
				lights_spot[i].atten_quad * l * l);

		float clamped_cos = max(0.0, dot(-L, normalize(light_spot_direction)));

		if (clamped_cos < cos(lights_spot[i].spot_cutoff)) // outside spotlight cone?
		{
			atten = 0.0;
		}
		else // inside spotlight cone
		{
			atten = atten * pow(clamped_cos, lights_spot[i].spot_exponent);   
		}

		float angle = max(0.0, dot(N,L));

		diffuse = atten * lights_spot[i].diffuse * front.diffuse * vec4(vec3(angle),1.0);

		// specular
		if (dot(N,L) < 0.0) // light source behind
		{
			specular = vec4(0.0, 0.0, 0.0, 0.0);
		}
		else // light source in front
		{
			specular = atten * lights_spot[i].specular * front.specular *
				vec4(vec3(pow(max(0.0, dot(reflect(-L,N), -P.xyz)), front.shininess)),1.0);
		}

		color += ambient + diffuse + specular;
	}
	for(int i = 0; i < light_count_directional; i++) // for all light sources
	{
		// ambient
		ambient = lights_directional[i].ambient * front.ambient;

		// diffuse
		atten = 1.0; // no atten

		// rotate to view space
		light_pos = mat3(view) * lights_directional[i].position.xyz;


		L = normalize(light_pos);


		float angle = max(0.0, dot(N,L));

		diffuse = atten * lights_directional[i].diffuse * front.diffuse * vec4(vec3(angle),1.0);

		// specular
		if (dot(N,L) < 0.0) // light source behind
		{
			specular = vec4(0.0, 0.0, 0.0, 0.0);
		}
		else // light source in front
		{
			specular = atten * lights_directional[i].specular * front.specular *
				vec4(vec3(pow(max(0.0, dot(reflect(-L,N), -P.xyz)), front.shininess)),1.0);
		}

		color += ambient + diffuse + specular;
	}
	color += emission;
	color += vec4(1,1,1,1);
}


