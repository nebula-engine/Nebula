#include <glm/gtc/matrix_transform.hpp>

#include <Nebula/App/Base.hh>
#include <Nebula/Graphics/Light/Spot.hh>

Neb::Light::Spot::Spot():
	spot_direction_(vec3(0.0, 0.0, -1.0)),
	spot_cutoff_(10.0),
	spot_exponent_(1.0),
	spot_light_cos_cutoff_(1.0)
{
}
void Neb::Light::Spot::load(int o, mat4 space) {
	GLUTPP_DEBUG_1_FUNCTION;
	
	auto p = Neb::App::Base::globalBase()->current_program();

	vec4 pos = pos_;

	pos += vec4(space[3][0], space[3][1], space[3][2], 0);

	pos.w = pos_.w;

	vec4 spot_direction(spot_direction_,0.0);
	
	spot_direction = space * spot_direction;
	
	
	
	//if(any(Neb::light::flag::e::SHOULD_LOAD_POS))
	{
		p->get_uniform_vector("lights.position")->load(o, pos);
		
		//unset(Neb::light::flag::e::SHOULD_LOAD_POS);
	}	
	//if(any(Neb::light::flag::e::SHOULD_LOAD_SPOT_DIRECTION))
	{
		p->get_uniform_vector("lights.spot_direction")->load(o, spot_direction);
		
		//unset(Neb::light::flag::e::SHOULD_LOAD_SPOT_DIRECTION);
	}
	
	//if(any(Neb::light::flag::e::SHOULD_LOAD_OTHER))
	{
		p->get_uniform_vector("lights.ambient")->load(o, ambient_);
		p->get_uniform_vector("lights.diffuse")->load(o, diffuse_);
		p->get_uniform_vector("lights.specular")->load(o, specular_);
		p->get_uniform_vector("lights.spot_cutoff")->load(o, spot_cutoff_);
		p->get_uniform_vector("lights.spot_exponent")->load(o, spot_exponent_);
		p->get_uniform_vector("lights.spot_light_cos_cutoff")->load(o, spot_light_cos_cutoff_);
		p->get_uniform_vector("lights.atten_const")->load(o, atten_const_);
		p->get_uniform_vector("lights.atten_linear")->load(o, atten_linear_);
		p->get_uniform_vector("lights.atten_quad")->load(o, atten_quad_);

		//unset(Neb::light::flag::e::SHOULD_LOAD_OTHER);
	}
}








