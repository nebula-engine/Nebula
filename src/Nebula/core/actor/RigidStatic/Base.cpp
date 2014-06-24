#include <gal/log/log.hpp>

#include <Nebula/debug.hh>
#include <Nebula/core/shape/Base.hh>
#include <Nebula/core/actor/RigidStatic/Base.hh>

	
neb::core::actor::rigidstatic::base::base(sp::shared_ptr<neb::core::actor::util::parent> parent):
		neb::core::actor::base(parent),
		neb::core::actor::actor::base(parent),
		neb::core::actor::rigidactor::base(parent)
{
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;
}
void		neb::core::actor::rigidstatic::base::init() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;
}
void		neb::core::actor::rigidstatic::base::step(gal::std::timestep const & ts) {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;
}

