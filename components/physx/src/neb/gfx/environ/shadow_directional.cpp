#include <gal/log/log.hpp>


#include <neb/core/util/debug.hpp>

#include <neb/gfx/app/__gfx_glsl.hpp>

#include <neb/gfx/camera/view/shadow_directional.hpp>
#include <neb/gfx/camera/proj/ortho.hpp>

#include <neb/gfx/environ/shadow/directional.hpp>
#include <neb/gfx/drawable/base.hpp>
#include <neb/gfx/util/log.hpp>
#include <neb/gfx/glsl/program/base.hpp>
#include <neb/gfx/core/light/directional.hpp>
#include <neb/gfx/RenderDesc.hpp>

neb::gfx::environ::shadow_directional::shadow_directional()
{
}
void		neb::gfx::environ::shadow_directional::init() {
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	auto self = std::dynamic_pointer_cast<neb::gfx::environ::shadow_directional>(shared_from_this());

//	auto light = light_.lock();
//	assert(light);

	programs_.d3_.reset(new neb::gfx::glsl::program::base("shadow"));
	programs_.d3_->init();
	
	programs_.d3_inst_.reset(new neb::gfx::glsl::program::base("shadow_inst"));
	programs_.d3_inst_->init();
	
	// camera
	view_.reset(new neb::gfx::camera::view::shadow_directional(self));

	proj_.reset(new neb::gfx::camera::proj::ortho(self));

}
void		neb::gfx::environ::shadow_directional::step(gal::etc::timestep const & ts) {

	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	if(proj_) proj_->step(ts);	
	if(view_) view_->step(ts);	

}
bool		neb::gfx::environ::shadow_directional::shouldRender()
{
	return true;
}
void		neb::gfx::environ::shadow_directional::render(std::shared_ptr<neb::gfx::context::base> context) {

	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	/**
	 * prepare rendering environment and then call the drawable
	 */

	
	auto drawable = drawable_.lock();

	if(!drawable) {
		LOG(lg, neb::gfx::sl, warning) << "environ has no drawable";
		return;
	}

	//auto self = std::dynamic_pointer_cast<neb::gfx::context::base>(shared_from_this());
	//auto app = neb::gfx::app::__gfx_glsl::global().lock();

	/** wrong for color maybe! */	
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	assert(proj_);
	assert(view_);
	
	//program_->use();

	//proj_->load(program_);
	//view_->load(program_);

	//glViewPort(0, 0, );

	//drawable->draw(context, program_, 0);

	drawable->draw(
			RenderDesc(
				view_.get(),
				proj_.get(),
				programs_.d3_.get(),
				programs_.d3_HF_.get(),
				programs_.d3_inst_.get())
		      );

}		




