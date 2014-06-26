#include <Galaxy-Log/log.hpp>

#include <neb/gfx/Context/Base.hh>
#include <neb/core/scene/Base.hh>

#include <neb/debug.hh>
#include <neb/util/typedef.hpp>
//#include <neb/simulation_callback.hh>
#include <neb/core/shape/base.hpp>

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
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;
}
phx::core::actor::actor::base::~base() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;

	assert(px_actor_ == NULL);
}
void		phx::core::actor::actor::base::init() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;

	phx::core::actor::base::init();
}
void		phx::core::actor::actor::base::setPose(neb::core::pose const & pose) {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;

	neb::core::actor::actor::base::setPose(pose);
	phx::core::actor::base::setPose(pose);
}
void		phx::core::actor::actor::base::step(gal::std::timestep const & ts) {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;

}
void		phx::core::actor::actor::base::releaseUp() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;

	//neb::core::actor::base::releaseUp();

	if(px_actor_ != NULL) {	
		px_actor_->release();
		px_actor_ = NULL;
	}
	
	//assert(!scene_.expired());

}

