
#define LIGHT_COUNT 8

uniform vec3	light_position[LIGHT_COUNT];
uniform vec4	light_ambient[LIGHT_COUNT];
uniform vec4	light_diffuse[LIGHT_COUNT];
uniform vec4	light_specular[LIGHT_COUNT];
uniform float	light_atten_const[LIGHT_COUNT];
uniform float	light_atten_linear[LIGHT_COUNT];
uniform float	light_atten_quad[LIGHT_COUNT];
uniform vec3	light_spot_direction[LIGHT_COUNT];
uniform float	light_spot_cutoff[LIGHT_COUNT];
uniform float	light_spot_exponent[LIGHT_COUNT];
uniform mat4	light_shadow_vpb_0[LIGHT_COUNT];
uniform mat4	light_shadow_vpb_1[LIGHT_COUNT];
uniform mat4	light_shadow_vpb_2[LIGHT_COUNT];
uniform mat4	light_shadow_vpb_3[LIGHT_COUNT];
uniform mat4	light_shadow_vpb_4[LIGHT_COUNT];
uniform mat4	light_shadow_vpb_5[LIGHT_COUNT];
uniform vec3	light_shadow_sampler_0[LIGHT_COUNT];
uniform vec3	light_shadow_sampler_1[LIGHT_COUNT];
uniform int	light_type[LIGHT_COUNT];
uniform int	light_closed[LIGHT_COUNT];
uniform int	light_count;

