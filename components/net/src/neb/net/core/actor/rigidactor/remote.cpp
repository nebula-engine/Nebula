#include <Galaxy-Log/log.hpp>
#include <neb/debug.hh>

#include <PhysX/core/actor/util/parent.hpp>
#include <PhysX/core/actor/rigidactor/remote.hpp>

phx::core::actor::rigidactor::remote::remote(std::shared_ptr<phx::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::actor::base(parent),
	neb::core::actor::rigidactor::base(parent),
	neb::core::actor::remote(parent),
	neb::core::actor::actor::remote(parent),
	neb::core::actor::rigidactor::remote(parent),
	phx::core::actor::base(parent),
	phx::core::actor::remote(parent),
	phx::core::actor::actor::base(parent),
	phx::core::actor::actor::remote(parent),
	phx::core::actor::rigidactor::base(parent)
{
}
void		phx::core::actor::rigidactor::remote::init() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;

	neb::core::actor::rigidactor::remote::init();
	phx::core::actor::actor::remote::init();
	phx::core::actor::rigidactor::base::init();
}
/*void		phx::core::actor::rigidactor::remote::release() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;

	neb::core::actor::rigidactor::base::release();
	phx::core::actor::actor::remote::release();
	phx::core::actor::rigidactor::base::release();

}*/
void		phx::core::actor::rigidactor::remote::step(gal::etc::timestep const & ts) {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;
	
	neb::core::actor::rigidactor::base::step(ts);
	phx::core::actor::actor::remote::step(ts);
	phx::core::actor::rigidactor::base::step(ts);
}




