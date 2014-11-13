
#include <Galaxy-Log/log.hpp>

#include <neb/app/Base.hh>
#include <neb/core/scene/Local.hh>
#include <neb/core/actor/RigidBody/Base.hh>
#include <neb/timer/Actor/Release.hpp>
#include <neb/debug.hh>



#include <PhysX/util/convert.hpp>
#include <PhysX/core/scene/local.hpp>
#include <PhysX/core/actor/rigiddynamic/local.hpp>
#include <PhysX/core/actor/rigidstatic/local.hpp>

phx::core::scene::local::local(std::shared_ptr<neb::core::scene::util::parent> parent):
	neb::core::scene::base(parent),
	neb::core::scene::local(parent),
	phx::core::scene::base(parent)
{
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core scene", debug) << __PRETTY_FUNCTION__;
}
void			phx::core::scene::local::init() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core scene", debug) << __PRETTY_FUNCTION__;

	neb::core::scene::local::init();
	phx::core::scene::base::init();
}
void			phx::core::scene::local::release() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core scene", debug) << __PRETTY_FUNCTION__;

	neb::core::scene::local::release();
	phx::core::scene::base::release();
}
void			phx::core::scene::local::step(gal::etc::timestep const & ts) {

}



