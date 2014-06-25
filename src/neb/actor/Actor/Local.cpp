#include <gal/log/log.hpp>
#include <neb/debug.hh>

#include <neb/core/actor/Actor/Local.hh>

neb::core::actor::actor::local::local(sp::shared_ptr<neb::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::actor::base(parent),
	neb::core::actor::local(parent)
{

}
void		neb::core::actor::actor::local::step(gal::std::timestep const & ts) {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;

	//	neb::core::actor::actor::base::step(dt);
	//	neb::core::actor::local::step(dt);
}

