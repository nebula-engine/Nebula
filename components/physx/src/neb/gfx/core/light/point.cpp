#include <gal/log/log.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <neb/core/util/debug.hpp>
#include <neb/core/util/log.hpp>

#include <neb/core/core/light/util/parent.hpp>

#include <neb/gfx/app/__gfx.hpp>
#include <neb/gfx/app/__gfx_glsl.hpp>
#include <neb/gfx/app/glfw.hpp>
#include <neb/gfx/window/Base.hh>
#include <neb/gfx/core/light/point.hpp>
#include <neb/gfx/glsl/uniform/vector.hpp>
#include <neb/gfx/glsl/program/base.hpp>
#include <neb/gfx/environ/shadow/point.hpp>
#include <neb/gfx/camera/proj/perspective.hpp>
#include <neb/gfx/camera/view/shadow/point.hpp>
#include <neb/gfx/Context/fbo_multi.hpp>
#include <neb/gfx/texture.hpp>
#include <neb/gfx/util/log.hpp>

#include <neb/phx/core/scene/base.hpp>

typedef neb::gfx::core::light::point THIS;

THIS::point()
{}
neb::gfx::core::light::type::e		THIS::getType()
{
	return neb::gfx::core::light::type::SPOT;
}
void	neb::gfx::core::light::point::load(neb::core::core::light::util::count & light_count, neb::core::pose const & pose) {

	LOG(lg, neb::core::core::light::sl, debug) << __PRETTY_FUNCTION__;
	assert(0);
	/*        
		  neb::gfx::core::light::base::load(light_count.point, pose);

		  auto p = neb::gfx::app::__gfx_glsl::global().lock()->current_program();


		  p->get_uniform_vector("lights_point.atten_const")->load(light_count.point, atten_const_);
		  p->get_uniform_vector("lights_point.atten_linear")->load(light_count.point, atten_linear_);
		  p->get_uniform_vector("lights_point.atten_quad")->load(light_count.point, atten_quad_);
		  light_count.point++;
		  */
}
void			neb::gfx::core::light::point::init(neb::core::core::light::util::parent * const & p)
{
	LOG(lg, neb::core::core::light::sl, debug) << __PRETTY_FUNCTION__;

	setParent(p);

	neb::gfx::core::light::base::init(p);
	
}	
void		neb::gfx::core::light::point::callbackPose(neb::core::pose const & gpose)
{
	LOG(lg, neb::gfx::core::light::sl, debug) << __PRETTY_FUNCTION__;
	LOG(lg, neb::gfx::core::light::sl, debug) << gpose.mat4_cast();
	
	light_array_slot_->set<0>(gpose.pos_);
}
void			neb::gfx::core::light::point::initShadow(std::shared_ptr<neb::gfx::environ::SceneDefault> e3)
{

	// scene
	auto scene = std::dynamic_pointer_cast<neb::phx::core::scene::base>(
			getScene()->shared_from_this()
			);

	auto self = std::dynamic_pointer_cast<neb::gfx::core::light::point>(shared_from_this());

	auto app = neb::gfx::app::glfw::global();

	typedef neb::gfx::window::base Window;
	auto window = app->neb::gfx::window::util::parent::create<Window>().lock();
	

	auto context = window->createContextFBOMulti().lock();

	auto environ = context->createEnvironShadowPoint().lock();

	context->setDrawable(scene);

	context->texture_ = scene->tex_shadow_map_;

	environ->light_ = self;

	setShadowEnviron(environ);

	// where shadows are rendered
	environ->environ_scene_ = e3;

}
void		neb::gfx::core::light::point::setShadowEnviron(std::shared_ptr<neb::gfx::environ::base> environ) {
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

	auto scene = dynamic_cast<neb::phx::core::scene::base*>(getScene());//getScene();

	// request texture layers
	texture_layers_ = scene->tex_shadow_map_->layer_slots_->reg(6);

	shadow_sampler_[0].x = texture_layers_->operator[](0);
	shadow_sampler_[0].y = texture_layers_->operator[](1);
	shadow_sampler_[0].z = texture_layers_->operator[](2);
	shadow_sampler_[1].x = texture_layers_->operator[](3);
	shadow_sampler_[1].y = texture_layers_->operator[](4);
	shadow_sampler_[1].z = texture_layers_->operator[](5);


	light_array_slot_->set<10>(shadow_vpb_[0]);
	light_array_slot_->set<11>(shadow_vpb_[1]);
	light_array_slot_->set<12>(shadow_vpb_[2]);
	light_array_slot_->set<13>(shadow_vpb_[3]);
	light_array_slot_->set<14>(shadow_vpb_[4]);
	light_array_slot_->set<15>(shadow_vpb_[5]);


	light_array_slot_->set<16>(shadow_sampler_[0]);
	light_array_slot_->set<17>(shadow_sampler_[1]);



}
void		THIS::load(ba::polymorphic_iarchive & ar, unsigned int const & v)
{
	LOG(lg, neb::core::core::shape::sl, debug) << __FUNCSIG__;

	gal::itf::shared::serialize(ar, v);
	neb::core::core::light::base::load(ar, v);
	neb::gfx::core::light::base::load(ar, v);
}
void		THIS::save(ba::polymorphic_oarchive & ar, unsigned int const & v) const
{
	LOG(lg, neb::core::core::shape::sl, debug) << __FUNCSIG__;

	const_cast<THIS*>(this)->gal::itf::shared::serialize(ar, v);
	neb::core::core::light::base::save(ar, v);
	neb::gfx::core::light::base::save(ar, v);
}



