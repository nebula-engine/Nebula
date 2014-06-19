#include <Galaxy-Log/log.hpp>

#include <Nebula/Graphics/Context/Base.hh>
#include <Nebula/Scene/Base.hh>

#include <Nebula/debug.hh>
#include <Nebula/Util/typedef.hpp>
//#include <Nebula/simulation_callback.hh>
#include <Nebula/Shape/Base.hh>

#include <PhysX/core/actor/util/parent.hpp>
#include <PhysX/core/actor/actor/base.hpp>
#include <PhysX/core/actor/rigiddynamic/local.hpp>
#include <PhysX/core/scene/base.hpp>

//neb::core::actor::actor::base::base() {
//}
phx::core::actor::actor::base::base(sp::shared_ptr<phx::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::actor::base(parent),
	phx::core::actor::base(parent),
	px_actor_(NULL)
{
	//NEBULA_ACTOR_BASE_FUNC;
}
void		phx::core::actor::actor::base::init() {
	//NEBULA_ACTOR_BASE_FUNC;

	phx::core::actor::base::init();
}
void		phx::core::actor::actor::base::setPose(neb::core::pose const & pose) {
	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;

	neb::core::actor::actor::base::setPose(pose);
	phx::core::actor::base::setPose(pose);
}
void		phx::core::actor::actor::base::step(neb::core::TimeStep const & ts) {
}


void		phx::core::actor::actor::base::release() {
	NEBULA_ACTOR_BASE_FUNC;
	
	neb::core::actor::base::release();

	//assert(!scene_.expired());

}

