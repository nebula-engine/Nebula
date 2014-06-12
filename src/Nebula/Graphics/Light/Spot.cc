#include <glm/gtc/matrix_transform.hpp>

#include <Nebula/App/Base.hh>
#include <Nebula/Graphics/Light/Spot.hh>
#include <Nebula/Graphics/glsl/Uniform/vector.hpp>


void neb::Light::Point::load(int o, mat4 space) {
	GLUTPP_DEBUG_1_FUNCTION;

	neb::Light::Base::load(o, space);

	auto p = neb::App::Base::global()->current_program();

	// tell shader this is not a spot light
	static const float spot_cutoff = 6;
	p->get_uniform_vector("lights.spot_cutoff")->load(o, spot_cutoff);
}

neb::Light::Spot::Spot(sp::shared_ptr<neb::Light::Util::Parent> parent):
	neb::Light::Base(parent),
	spot_direction_(vec3(0.0, 0.0, -1.0)),
	spot_cutoff_(10.0),
	spot_exponent_(1.0),
	spot_light_cos_cutoff_(1.0)
{
}
void neb::Light::Spot::load(int o, mat4 space) {
	GLUTPP_DEBUG_1_FUNCTION;

	neb::Light::Base::load(o, space);
	
	auto p = neb::App::Base::global()->current_program();

	vec4 pos = pos_;

	pos += vec4(space[3][0], space[3][1], space[3][2], 0);

	pos.w = pos_.w;

	vec4 spot_direction(spot_direction_,0.0);
	
	spot_direction = space * spot_direction;
	
	
	
	p->get_uniform_vector("lights.spot_direction")->load(o, spot_direction);

	p->get_uniform_vector("lights.spot_cutoff")->load(o, spot_cutoff_);
	p->get_uniform_vector("lights.spot_exponent")->load(o, spot_exponent_);
	p->get_uniform_vector("lights.spot_light_cos_cutoff")->load(o, spot_light_cos_cutoff_);
}








