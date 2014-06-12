#include <glm/gtc/matrix_transform.hpp>

#include <Nebula/App/Base.hh>
#include <Nebula/Graphics/Light/Spot.hh>
#include <Nebula/Graphics/glsl/Uniform/vector.hpp>

neb::Light::Point::Point(sp::shared_ptr<neb::Light::Util::Parent> parent):
	neb::Light::Base(parent, "lights_point"),
	atten_const_(1.0),
	atten_linear_(0.0),
	atten_quad_(0.0)

{}
void		neb::Light::Point::load(neb::core::light::util::count & light_count, mat4 space) {
	GLUTPP_DEBUG_1_FUNCTION;
	
	neb::Light::Base::load(light_count.point, space);
	
	auto p = neb::App::Base::global()->current_program();
	
	
	p->get_uniform_vector("lights_point.atten_const")->load(light_count.point, atten_const_);
	p->get_uniform_vector("lights_point.atten_linear")->load(light_count.point, atten_linear_);
	p->get_uniform_vector("lights_point.atten_quad")->load(light_count.point, atten_quad_);
	light_count.point++;
}

neb::Light::Spot::Spot(sp::shared_ptr<neb::Light::Util::Parent> parent):
	neb::Light::Base(parent, "lights_spot"),
	spot_direction_(vec3(0.0, 0.0, -1.0)),
	spot_cutoff_(10.0),
	spot_exponent_(1.0),
	spot_light_cos_cutoff_(1.0),
	atten_const_(1.0),
	atten_linear_(0.0),
	atten_quad_(0.0)
{
}
void neb::Light::Spot::load(neb::core::light::util::count & light_count, mat4 space) {
	GLUTPP_DEBUG_1_FUNCTION;

	neb::Light::Base::load(light_count.spot, space);

	auto p = neb::App::Base::global()->current_program();

	vec4 pos = pos_;

	pos += vec4(space[3][0], space[3][1], space[3][2], 0);

	pos.w = pos_.w;

	vec4 spot_direction(spot_direction_,0.0);

	spot_direction = space * spot_direction;

	p->get_uniform_vector("lights_spot.atten_const")->load(light_count.spot, atten_const_);
	p->get_uniform_vector("lights_spot.atten_linear")->load(light_count.spot, atten_linear_);
	p->get_uniform_vector("lights_spot.atten_quad")->load(light_count.spot, atten_quad_);


	p->get_uniform_vector("lights_spot.spot_direction")->load(light_count.spot, spot_direction);
	p->get_uniform_vector("lights_spot.spot_cutoff")->load(light_count.spot, spot_cutoff_);
	p->get_uniform_vector("lights_spot.spot_exponent")->load(light_count.spot, spot_exponent_);
	p->get_uniform_vector("lights_spot.spot_light_cos_cutoff")->load(light_count.spot, spot_light_cos_cutoff_);

	light_count.spot++;
}








