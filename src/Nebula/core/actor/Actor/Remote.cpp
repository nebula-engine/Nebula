#include <Nebula/debug.hh>

#include <Nebula/core/actor/Actor/Remote.hh>


neb::core::actor::actor::remote::remote(sp::shared_ptr<neb::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::actor::base(parent),
	neb::core::actor::remote(parent)
{

}
void		neb::core::actor::actor::remote::step(gal::std::timestep const & ts) {
	//if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "neb core actor", debug) << __PRETTY_FUNCTION__;

//	neb::core::actor::actor::base::step(time, dt);
//	neb::core::actor::remote::step(time, dt);
}



