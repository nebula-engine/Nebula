
#include <neb/core/util/cast.hpp>

#include <neb/gfx/util/log.hpp>
#include <neb/gfx/camera/view/ridealong.hh>
#include <neb/gfx/camera/view/Free.hh>
#include <neb/gfx/environ/SceneDefault.hpp>
#include <neb/gfx/RenderDesc.hpp>

#include <neb/phx/core/scene/base.hpp>

void		neb::gfx::environ::SceneDefault::init()
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	auto self = std::dynamic_pointer_cast<neb::gfx::environ::three>(shared_from_this());
	
	neb::gfx::environ::single<neb::gfx::camera::view::base>::init();
	neb::gfx::environ::three::init();

	//programs_.reset(new neb::gfx::glsl::program::threed("3d"));
	//programs_->init();


	// camera
	if(!view_) {
		view_.reset(new neb::gfx::camera::view::Free(self));
	}


}


std::weak_ptr<neb::gfx::camera::view::ridealong>		neb::gfx::environ::SceneDefault::createViewridealong(
		std::weak_ptr<neb::core::core::actor::base> actor)
{
	auto self(std::dynamic_pointer_cast<neb::gfx::environ::three>(shared_from_this()));

	typedef neb::gfx::camera::view::ridealong T;
	
	std::shared_ptr<T> view(new T(self, actor));

	view_ = view;

	return view;
}

void		neb::gfx::environ::SceneDefault::render(std::shared_ptr<neb::gfx::context::base> context) {

	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	// prepare rendering environment and then call the drawable

	
	auto drawable = drawable_.lock();

	if(!drawable) {
		LOG(lg, neb::gfx::sl, warning) << "drawable is NULL";
		return;
	}

	//auto self = std::dynamic_pointer_cast<neb::gfx::context::base>(shared_from_this());
	//auto app = neb::gfx::app::__gfx_glsl::global().lock();

	// wrong for color maybe! 	
	//glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	//assert(proj_);
	//assert(view_);
	
	//program_->use();
	
	viewport_.load();
	
	//proj_->load(program_);
	//view_->load(program_);
	
	drawable->draw(
			RenderDesc(
				view_.get(),
				proj_.get(),
				programs_.d3_.get(),
				programs_.d3_HF_.get(),
				programs_.d3_inst_.get()
				)
		      );

	auto scene = neb::could_be<neb::gfx::drawable::base, neb::phx::core::scene::base>(drawable);

	if(scene) scene->drawDebug(
				RenderDesc(
					view_.get(),
					proj_.get(),
					programs_.d3_.get(),
					programs_.d3_HF_.get(),
					programs_.d3_inst_.get()
					)
				);

	if(0) { /** @todo make this a dynamic flag! */
		if(scene) scene->drawPhysxVisualization(
				RenderDesc(
					view_.get(),
					proj_.get(),
					programs_.d3_.get(),
					programs_.d3_HF_.get(),
					programs_.d3_inst_.get()
					)
				);
	}
}	

