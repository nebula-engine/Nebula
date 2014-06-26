#include <gal/log/log.hpp>

#include <neb/debug.hh>
#include <neb/core/light/util/parent.hpp>
#include <neb/core/light/base.hpp>

neb::core::light::base::base(sp::shared_ptr<neb::core::light::util::parent> parent):
	parent_(parent),
	pos_(vec4(0.0, 0.0, 0.0, 1.0))
{}
void neb::core::light::base::init() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core light", debug) << __PRETTY_FUNCTION__;

}
void neb::core::light::base::release() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core light", debug) << __PRETTY_FUNCTION__;
}
void				neb::core::light::base::step(gal::std::timestep const & ts) {

}
neb::core::pose			neb::core::light::base::getPose() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core light", debug) << __PRETTY_FUNCTION__;
	
	auto parent(parent_.lock());
	assert(parent);
	
	auto p = parent->getPoseGlobal();
	
	return p;
}
vec4				neb::core::light::base::getPos() {
	return vec4(pos_, 1.0);
}




