
#include <neb/core/util/cast.hpp>

#include <neb/gfx/util/log.hpp>
#include <neb/gfx/camera/view/ridealong.hh>
#include <neb/gfx/camera/view/manual.hpp>
#include <neb/gfx/environ/NormalMap.hpp>
#include <neb/gfx/RenderDesc.hpp>

#include <neb/phx/core/scene/base.hpp>

typedef neb::gfx::environ::NormalMap THIS;

void		THIS::init()
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	auto self = std::dynamic_pointer_cast<neb::gfx::environ::three>(shared_from_this());
	
	neb::gfx::environ::single<neb::gfx::camera::view::base>::init();
	neb::gfx::environ::three::init();

	programs_.d3_.reset(new neb::gfx::glsl::program::base("3d"));
	programs_.d3_->init();

	programs_.d3_HF_.reset(new neb::gfx::glsl::program::base("normal_map"));
	programs_.d3_HF_->init();

	programs_.d3_inst_.reset(new neb::gfx::glsl::program::base("3d_inst"));
	programs_.d3_inst_->init();


	// camera
	if(!view_) {
		view_.reset(new neb::gfx::camera::view::manual(self));
	}


}


void		THIS::render(std::shared_ptr<neb::gfx::context::base> context)
{

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
	
	drawable->draw(
			RenderDesc(
				view_.get(),
				proj_.get(),
				programs_.d3_.get(),
				programs_.d3_HF_.get(),
				programs_.d3_inst_.get()
				)
		      );

}	


