//#include <assert.h>
#include <Galaxy-Log/log.hpp>

#include <Nebula/App/Base.hh>
#include <Nebula/Scene/Base.hh>
#include <Nebula/Graphics/Context/Base.hh>
#include <Nebula/Graphics/environ/base.hpp>
#include <Nebula/Graphics/GUI/Layout/Base.hh>
#include <Nebula/Graphics/Camera/View/Free.hh>
#include <Nebula/Graphics/Camera/Projection/Perspective.hh>


neb::gfx::context::base::base() {
}
neb::gfx::context::base::base(sp::shared_ptr<neb::gfx::context::util::parent> parent): parent_(parent) {

	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx context", debug) << __PRETTY_FUNCTION__;
}
neb::gfx::context::base&		neb::gfx::context::base::operator=(neb::gfx::context::base const & r){
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx context", debug) << __PRETTY_FUNCTION__;
	return *this;
}
void		neb::gfx::context::base::init() {
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx context", debug) << __PRETTY_FUNCTION__;
	
	
}
void		neb::gfx::context::base::release() {
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx context", debug) << __PRETTY_FUNCTION__;
}
void		neb::gfx::context::base::resize(int w, int h) {
	if(environ_) environ_->resize(w,h);
}
void		neb::gfx::context::base::step(neb::core::TimeStep const & ts) {

	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx context", debug) << __PRETTY_FUNCTION__;
	
	if(environ_) environ_->step(ts);	

}
void		neb::gfx::context::base::render() {
	
	BOOST_LOG_CHANNEL_SEV(lg, "neb gfx context", debug) << __PRETTY_FUNCTION__;

	/**
	 * prepare rendering environment and then call the drawable
	 */

	GLUTPP_DEBUG_1_FUNCTION;

	if(!environ_) return;
	
	auto self = sp::dynamic_pointer_cast<neb::gfx::context::base>(shared_from_this());
	assert(self);

	environ_->render(self);
	
}		





