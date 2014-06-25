#include <Galaxy-Log/log.hpp>

#include <neb/app/Base.hh>
#include <neb/debug.hh>

#include <neb/gfx/Camera/View/Free.hh>
#include <neb/gfx/Camera/Projection/Perspective.hh>

#include <neb/gfx/environ/three.hpp>

void		neb::gfx::environ::three::init() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx environ", debug) << __PRETTY_FUNCTION__;

	auto self = sp::dynamic_pointer_cast<neb::gfx::environ::three>(shared_from_this());
	
	// camera
	if(!view_) {
		view_.reset(new neb::gfx::Camera::View::Free(self));
	}

	proj_.reset(new neb::gfx::Camera::Projection::Perspective(self));
	//camera_->init(shared_from_this());
	
}
void		neb::gfx::environ::three::step(gal::std::timestep const & ts) {

	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx environ", debug) << __PRETTY_FUNCTION__;

	if(proj_) proj_->step(ts);	
	if(view_) view_->step(ts);	

}
void		neb::gfx::environ::three::render(sp::shared_ptr<neb::gfx::context::base> context) {

	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx environ", debug) << __PRETTY_FUNCTION__;

	/**
	 * prepare rendering environment and then call the drawable
	 */

	
	auto drawable = drawable_.lock();

	if(!drawable) return;

	//auto self = sp::dynamic_pointer_cast<neb::gfx::context::base>(shared_from_this());
	auto app = neb::app::base::global();

	/** wrong for color maybe! */	
	//glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	assert(proj_);
	assert(view_);
	
	// get program choice from drawable
	/** @todo replace with 'environ' which determines program and camera types and accepts certian types of drawables */
	
	auto p = app->use_program(neb::program_name::e::LIGHT);
	
	//viewport_.load();


	proj_->load(p);
	view_->load(p);

	drawable->draw(context, p);
}		





