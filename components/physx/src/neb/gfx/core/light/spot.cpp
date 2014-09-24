#include <gal/log/log.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <neb/core/util/debug.hpp>

#include <neb/core/core/light/util/parent.hpp>

#include <neb/gfx/util/log.hpp>
#include <neb/gfx/app/__gfx_glsl.hpp>
#include <neb/gfx/core/light/spot.hpp>
#include <neb/gfx/glsl/uniform/vector.hpp>
#include <neb/gfx/glsl/program/base.hpp>

#include <neb/phx/core/scene/base.hpp>

typedef neb::gfx::core::light::spot THIS;

THIS::spot()
{
}
neb::gfx::core::light::type::e		THIS::getType()
{
	return neb::gfx::core::light::type::SPOT;
}
void			THIS::init(neb::core::core::light::util::parent * const & p)
{
	LOG(lg, neb::gfx::core::light::sl, debug) << __PRETTY_FUNCTION__;

	setParent(p);

	neb::gfx::core::light::base::init(p);
}
void			neb::gfx::core::light::spot::load(
		neb::core::core::light::util::count & light_count,
		neb::core::pose const & pose) {

/*	neb::gfx::core::light::base::load(light_count.spot, pose);
	
	auto p = neb::gfx::app::__gfx_glsl::global().lock()->current_program();
	
	vec4 spot_direction(spot_direction_,0.0);

	spot_direction = pose.rot_ * spot_direction;

	p->get_uniform_vector("lights_spot.atten_const")->load(light_count.spot, atten_const_);
	p->get_uniform_vector("lights_spot.atten_linear")->load(light_count.spot, atten_linear_);
	p->get_uniform_vector("lights_spot.atten_quad")->load(light_count.spot, atten_quad_);


	p->get_uniform_vector("lights_spot.spot_direction")->load(light_count.spot, spot_direction);
	p->get_uniform_vector("lights_spot.spot_cutoff")->load(light_count.spot, spot_cutoff_);
	p->get_uniform_vector("lights_spot.spot_exponent")->load(light_count.spot, spot_exponent_);
	p->get_uniform_vector("lights_spot.spot_light_cos_cutoff")->load(light_count.spot, spot_light_cos_cutoff_);

	light_count.spot++;
	*/
}
void		neb::gfx::core::light::spot::callbackPose(neb::core::pose const & gpose)
{
	LOG(lg, neb::gfx::core::light::sl, debug) << __PRETTY_FUNCTION__;
	LOG(lg, neb::gfx::core::light::sl, debug) << gpose.mat4_cast();
	
	light_array_slot_->set<0>(gpose.pos_);
	light_array_slot_->set<7>(gpose.rot_ * spot_direction_);
}
void		neb::gfx::core::light::spot::setShadowEnviron(std::shared_ptr<neb::gfx::environ::base> environ) {
/*
	assert(environ);
	shadow_environ_ = environ;
	auto e = std::dynamic_pointer_cast<neb::gfx::environ::shadow::point>(environ);
	assert(e);

	auto proj = e->proj_->proj();

	static const glm::mat4 bias(
			0.5f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.5f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.5f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f);

	glm::mat4 pb = bias * proj;
	glm::mat4 vpb;

	for(GLint layer = 0; layer < 6; layer++) {

		auto view = e->view_[layer]->view();

		vpb = pb * view;
		shadow_vpb_[layer] = vpb;

	}

	auto scene = getScene();

	// request texture layers
	texture_layers_ = scene->tex_shadow_map_->layer_slots_->reg(6);

	shadow_sampler_[0].x = texture_layers_->operator[](0);
	shadow_sampler_[0].y = texture_layers_->operator[](1);
	shadow_sampler_[0].z = texture_layers_->operator[](2);
	shadow_sampler_[1].x = texture_layers_->operator[](3);
	shadow_sampler_[1].y = texture_layers_->operator[](4);
	shadow_sampler_[1].z = texture_layers_->operator[](5);

	auto parent = getScene();

	parent->light_array_[light_array_].set_shadow_vpb_0(light_array_slot_, shadow_vpb_[0]);
	parent->light_array_[light_array_].set_shadow_vpb_1(light_array_slot_, shadow_vpb_[1]);
	parent->light_array_[light_array_].set_shadow_vpb_2(light_array_slot_, shadow_vpb_[2]);
	parent->light_array_[light_array_].set_shadow_vpb_3(light_array_slot_, shadow_vpb_[3]);
	parent->light_array_[light_array_].set_shadow_vpb_4(light_array_slot_, shadow_vpb_[4]);
	parent->light_array_[light_array_].set_shadow_vpb_5(light_array_slot_, shadow_vpb_[5]);


	parent->light_array_[light_array_].set_shadow_sampler_0(light_array_slot_, shadow_sampler_[0]);
	parent->light_array_[light_array_].set_shadow_sampler_1(light_array_slot_, shadow_sampler_[1]);
*/

	shadow_sampler_[0].x = -1;
	shadow_sampler_[0].y = -1;
	shadow_sampler_[0].z = -1;
	shadow_sampler_[1].x = -1;
	shadow_sampler_[1].y = -1;
	shadow_sampler_[1].z = -1;


}
void		THIS::load(ba::polymorphic_iarchive & ar, unsigned int const &)
{
	LOG(lg, neb::gfx::core::light::sl, debug) << __FUNCSIG__;

	BOOST_SERIALIZATION_BASE_OBJECT_NVP(gal::itf::shared);
	BOOST_SERIALIZATION_BASE_OBJECT_NVP(neb::core::core::light::base);
}
void		THIS::save(ba::polymorphic_oarchive & ar, unsigned int const &) const
{
	LOG(lg, neb::gfx::core::light::sl, debug) << __FUNCSIG__;

	BOOST_SERIALIZATION_BASE_OBJECT_NVP(gal::itf::shared);
	BOOST_SERIALIZATION_BASE_OBJECT_NVP(neb::core::core::light::base);
}








