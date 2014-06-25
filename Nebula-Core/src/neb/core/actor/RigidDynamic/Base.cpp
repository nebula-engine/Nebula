#include <gal/log/log.hpp>

#include <neb/debug.hh>
#include <neb/core/shape/Base.hh>
#include <neb/core/actor/RigidDynamic/Base.hh>

//neb::core::actor::rigiddynamic::base::base() {
//}

neb::core::actor::rigiddynamic::base::base(sp::shared_ptr<neb::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::actor::base(parent),
	neb::core::actor::rigidactor::base(parent),
	neb::core::actor::rigidbody::base(parent)
{
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;
}
void		neb::core::actor::rigiddynamic::base::init() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;

	neb::core::actor::rigidbody::base::init();
	
}

