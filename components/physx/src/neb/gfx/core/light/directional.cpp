#include <neb/core/core/light/util/parent.hpp>

#include <neb/gfx/core/light/directional.hpp>
#include <neb/gfx/environ/shadow/directional.hpp>
#include <neb/gfx/app/__gfx_glsl.hpp>
//#include <neb/gfx/app/__gfx.hpp>
#include <neb/gfx/app/glfw.hpp>
#include <neb/gfx/core/light/base.hpp>
#include <neb/gfx/window/Base.hh>
#include <neb/gfx/free.hpp>
#include <neb/gfx/glsl/uniform/vector.hpp>
#include <neb/gfx/camera/proj/base.hpp>
#include <neb/gfx/camera/view/Base.hh>
#include <neb/gfx/Context/fbo.hpp>
#include <neb/gfx/util/log.hpp>
#include <neb/phx/core/scene/base.hpp>

typedef neb::gfx::core::light::directional THIS;

THIS::directional()
{

}
neb::gfx::core::light::type::e		THIS::getType()
{
	return neb::gfx::core::light::type::DIRECTIONAL;
}
void			neb::gfx::core::light::directional::init(neb::core::core::light::util::parent * const & p)
{
	setParent(p);
	
	neb::gfx::core::light::base::init(p);
	
	auto scene = std::dynamic_pointer_cast<neb::phx::core::scene::base>(
		getScene()->shared_from_this()
		);

	auto self = std::dynamic_pointer_cast<neb::gfx::core::light::directional>(shared_from_this());
	
	auto app = neb::gfx::app::glfw::global();

	
	auto window = app->neb::gfx::window::util::parent::create<neb::gfx::window::base>().lock();

	auto context = window->createContextFBO().lock();
	
	auto environ = context->createEnvironShadowDirectional().lock();
	
	context->setDrawable(scene);
	
	context->texture_ = scene->tex_shadow_map_;

	environ->light_ = self;

	setShadowEnviron(environ);

}
void		neb::gfx::core::light::directional::callbackPose(neb::core::pose const & gpose)
{
	LOG(lg, neb::gfx::core::light::sl, debug) << __PRETTY_FUNCTION__;
	LOG(lg, neb::gfx::core::light::sl, debug) << gpose.mat4_cast();
	
	//auto scene = getScene();
	
	//scene->light_array_[light_array_].set_pos(light_array_slot_, gpose.pos_);
}
void		neb::gfx::core::light::directional::setShadowEnviron(std::shared_ptr<neb::gfx::environ::base> environ) {
	assert(environ);
	shadow_environ_ = environ;
	auto e = std::dynamic_pointer_cast<neb::gfx::environ::shadow_directional>(environ);
	assert(e);
	
	auto proj = e->proj_->proj();
	auto view = e->view_->view();

	static const glm::mat4 bias(
			0.5f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.5f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.5f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f);

	glm::mat4 vpb = bias * proj * view;
	
	// request texture layers
	auto scene = dynamic_cast<neb::phx::core::scene::base*>(getScene());

	texture_layers_ = scene->tex_shadow_map_->layer_slots_->reg(1);

	shadow_sampler_[0].x = texture_layers_->operator[](0);

	shadow_vpb_[0] = vpb;
	
	// light array
	
	light_array_slot_->set<10>(shadow_vpb_[0]);
			
	light_array_slot_->set<16>(shadow_sampler_[0]);

}
void		THIS::load(ba::polymorphic_iarchive & ar, unsigned int const &)
{
	LOG(lg, neb::gfx::core::light::sl, debug) << __PRETTY_FUNCTION__;

	BOOST_SERIALIZATION_BASE_OBJECT_NVP(gal::itf::shared);
	BOOST_SERIALIZATION_BASE_OBJECT_NVP(neb::core::core::light::base);
}
void		THIS::save(ba::polymorphic_oarchive & ar, unsigned int const &) const
{
	LOG(lg, neb::gfx::core::light::sl, debug) << __PRETTY_FUNCTION__;

	BOOST_SERIALIZATION_BASE_OBJECT_NVP(gal::itf::shared);
	BOOST_SERIALIZATION_BASE_OBJECT_NVP(neb::core::core::light::base);
}



