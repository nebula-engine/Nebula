
#include <neb/core/actor/RigidStatic/remote.hpp>

	
neb::core::actor::rigidstatic::remote::remote(sp::shared_ptr<neb::core::actor::util::parent> parent):
		neb::core::actor::base(parent),
		neb::core::actor::actor::base(parent),
		neb::core::actor::rigidactor::base(parent),
		neb::core::actor::remote(parent),
		neb::core::actor::actor::remote(parent),
		neb::core::actor::rigidactor::remote(parent),
		neb::core::actor::rigidstatic::base(parent)
{
	//if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__
}
void		neb::core::actor::rigidstatic::remote::init() {
	//if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__
}
void		neb::core::actor::rigidstatic::remote::release() {
	//if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__
}
void		neb::core::actor::rigidstatic::remote::step(gal::std::timestep const & ts) {
	//if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;
}

