#include <neb/gfx/app/__gfx_glsl.hpp>
#include <neb/gfx/drawable/base.hpp>
#include <neb/gfx/environ/two.hpp>
#include <neb/gfx/glsl/program/base.hpp>
#include <neb/gfx/RenderDesc.hpp>
void		neb::gfx::environ::two::render(std::shared_ptr<neb::gfx::context::base> context) {
	/**
	 * prepare rendering environment and then call the drawable
	 */

	//GLUTPP_DEBUG_1_FUNCTION;
	
	auto drawable = drawable_.lock();

	if(!drawable) return;

	//auto self = std::dynamic_pointer_cast<neb::gfx::context::base>(shared_from_this());
	auto app = neb::gfx::app::__gfx_glsl::global().lock();

	/** wrong for color maybe! */	
	//glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	
	// get program choice from drawable
	/** @todo replace with 'environ' which determines program and camera types and accepts certian types of drawables */
	
	
	app->program_text_->use();
	
	//drawable->draw(context, app->program_text_, 0);
	drawable->draw(RenderDesc());
}		





