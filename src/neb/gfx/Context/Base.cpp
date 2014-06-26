//#include <assert.h>
#include <Galaxy-Log/log.hpp>

#include <neb/debug.hh>
#include <neb/app/Base.hh>
#include <neb/core/scene/base.hpp>
#include <neb/gfx/Context/Base.hh>
#include <neb/gfx/environ/base.hpp>
#include <neb/gfx/GUI/Layout/Base.hh>
#include <neb/gfx/Camera/View/Free.hh>
#include <neb/gfx/Camera/Projection/Perspective.hh>


neb::gfx::context::base::base() {
}
neb::gfx::context::base::base(sp::shared_ptr<neb::gfx::context::util::parent> parent): parent_(parent) {

	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx context", debug) << __PRETTY_FUNCTION__;
}
neb::gfx::context::base&		neb::gfx::context::base::operator=(neb::gfx::context::base const & r){
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx context", debug) << __PRETTY_FUNCTION__;
	return *this;
}
void		neb::gfx::context::base::init() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx context", debug) << __PRETTY_FUNCTION__;
	
	
}
void		neb::gfx::context::base::release() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx context", debug) << __PRETTY_FUNCTION__;
}
void		neb::gfx::context::base::resize(int w, int h) {
	if(environ_) environ_->resize(w,h);
}
void		neb::gfx::context::base::step(gal::std::timestep const & ts) {

	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx context", debug) << __PRETTY_FUNCTION__;
	
	if(environ_) environ_->step(ts);	

}
void		neb::gfx::context::base::render() {
	
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb gfx context", debug) << __PRETTY_FUNCTION__;

	/**
	 * prepare rendering environment and then call the drawable
	 */


	if(!environ_) return;
	
	auto self = sp::dynamic_pointer_cast<neb::gfx::context::base>(shared_from_this());
	assert(self);

	environ_->render(self);
	
}		





