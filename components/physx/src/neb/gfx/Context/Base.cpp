
#include <gal/log/log.hpp>
#include <gal/stl/deleter.hpp>

#include <neb/core/util/debug.hpp>
#include <neb/core/core/scene/base.hpp>

#include <neb/gfx/window/Base.hh>
#include <neb/gfx/Context/Base.hh>
#include <neb/gfx/Context/Window.hpp>
#include <neb/gfx/Context/Util/Parent.hh>
#include <neb/gfx/environ/two.hpp>
#include <neb/gfx/environ/SceneDefault.hpp>
#include <neb/gfx/environ/NormalMap.hpp>
#include <neb/gfx/environ/shadow/point.hpp>
#include <neb/gfx/environ/shadow/directional.hpp>
#include <neb/gfx/environ/vis_depth.hpp>
#include <neb/gfx/gui/layout/base.hpp>
#include <neb/gfx/camera/view/Free.hh>
#include <neb/gfx/camera/proj/perspective.hpp>
#include <neb/gfx/util/log.hpp>

/*neb::gfx::context::base::base() {
}*/
neb::gfx::context::base::base()
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
}
/*neb::gfx::context::base&		neb::gfx::context::base::operator=(neb::gfx::context::base const & r){
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
	return *this;
}*/
/*void		neb::gfx::context::base::init() {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
}
void		neb::gfx::context::base::release() {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
}*/
void		neb::gfx::context::base::resize(int w, int h) {
	if(environ_) environ_->resize(w,h);
}
void		neb::gfx::context::base::step(gal::etc::timestep const & ts) {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
	if(environ_) environ_->step(ts);	
}
void		neb::gfx::context::base::render() {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
	/**
	 * prepare rendering environment and then call the drawable
	 */
	if(!environ_)
	{
		LOG(lg, neb::gfx::sl, warning) << "context has no environ";
		return;
	}

	auto self = std::dynamic_pointer_cast<neb::gfx::context::base>(shared_from_this());
	assert(self);
	
	environ_->render(self);
}		
std::weak_ptr<neb::gfx::environ::two>			neb::gfx::context::base::createEnvironTwo()
{
	auto environ = sp::make_shared<neb::gfx::environ::two>();
	
	auto w = getParent()->isWindowBase();
	if(w)
	{
		w->makeCurrent();
	}

	environ->init();

	environ_ = environ;
	
	return environ;
}
std::weak_ptr<neb::gfx::environ::SceneDefault>		neb::gfx::context::base::createEnvironSceneDefault() {

	typedef neb::gfx::environ::SceneDefault E;
	
	std::shared_ptr<E> environ(new E(), gal::stl::deleter<E>());

	auto w = getParent()->isWindowBase();
	if(w)
	{
		w->makeCurrent();
	}

	environ->init();

	environ_ = environ;

	return environ;
}
std::weak_ptr<neb::gfx::environ::NormalMap>		neb::gfx::context::base::createEnvironNormalMap() {

	typedef neb::gfx::environ::NormalMap E;
	
	std::shared_ptr<E> environ(new E(), gal::stl::deleter<E>());

	auto w = getParent()->isWindowBase();
	if(w)
	{
		w->makeCurrent();
	}

	environ->init();

	environ_ = environ;

	return environ;
}
std::weak_ptr<neb::gfx::environ::vis_depth>		neb::gfx::context::base::createEnvironVisDepth() {

	auto environ = std::make_shared<neb::gfx::environ::vis_depth>();

	auto p = getParent();
	auto w = p->isWindowBase();
	if(w)
	{
		w->makeCurrent();
	}

	environ->init();
	
	environ_ = environ;
	
	return environ;
}
std::weak_ptr<neb::gfx::environ::shadow_directional>	neb::gfx::context::base::createEnvironShadowDirectional() {

	typedef neb::gfx::environ::shadow_directional E;

	std::shared_ptr<E> environ (new E());

	auto p = getParent();
	auto w = p->isWindowBase();
	if(w)
	{
		w->makeCurrent();
	}

	environ->init();
	
	environ_ = environ;
	
	return environ;
}
std::weak_ptr<neb::gfx::environ::shadow::point>		neb::gfx::context::base::createEnvironShadowPoint() {

	auto environ = sp::make_shared<neb::gfx::environ::shadow::point>();

	auto p = getParent();
	auto w = p->isWindowBase();
	if(w)
	{
		w->makeCurrent();
	}

	environ->init();
	
	environ_ = environ;
	
	return environ;
}
void							neb::gfx::context::base::setDrawable(std::shared_ptr<neb::gfx::drawable::base> drawable) {
	assert(environ_);
	environ_->drawable_ = drawable;
}



