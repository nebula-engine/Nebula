#include <gal/log/log.hpp>

#include <Nebula/debug.hh>
#include <Nebula/core/shape/Base.hh>
#include <Nebula/core/actor/RigidStatic/local.hpp>

	
neb::core::actor::rigidstatic::local::local(sp::shared_ptr<neb::core::actor::util::parent> parent):
		neb::core::actor::base(parent),
		neb::core::actor::actor::base(parent),
		neb::core::actor::rigidactor::base(parent),
		neb::core::actor::local(parent),
		neb::core::actor::actor::local(parent),
		neb::core::actor::rigidactor::local(parent),
		neb::core::actor::rigidstatic::base(parent)
{
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;
}
void		neb::core::actor::rigidstatic::local::init() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;
}
void		neb::core::actor::rigidstatic::local::release() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;
}
void		neb::core::actor::rigidstatic::local::step(gal::std::timestep const & ts) {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;
}

