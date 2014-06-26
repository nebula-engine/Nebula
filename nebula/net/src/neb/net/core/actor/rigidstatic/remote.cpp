#include <Galaxy-Log/log.hpp>

#include <neb/debug.hh>
//#include <neb/Physics.hh>
#include <neb/core/shape/base.hpp>

#include <PhysX/app/base.hpp>
#include <PhysX/util/convert.hpp>
#include <PhysX/core/actor/util/parent.hpp>
#include <PhysX/core/actor/rigidstatic/remote.hpp>
#include <PhysX/core/scene/base.hpp>

phx::core::actor::rigidstatic::remote::remote(sp::shared_ptr<phx::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::actor::base(parent),
	neb::core::actor::rigidactor::base(parent),
	neb::core::actor::remote(parent),
	neb::core::actor::actor::remote(parent),
	neb::core::actor::rigidactor::remote(parent),
	neb::core::actor::rigidstatic::base(parent),
	neb::core::actor::rigidstatic::remote(parent),
	phx::core::actor::base(parent),
	phx::core::actor::remote(parent),
	phx::core::actor::actor::base(parent),
	phx::core::actor::actor::remote(parent),
	phx::core::actor::rigidactor::base(parent),
	phx::core::actor::rigidactor::remote(parent),
	phx::core::actor::rigidstatic::base(parent)
{
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;
}
void			phx::core::actor::rigidstatic::remote::init() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;
	
	neb::core::actor::rigidstatic::remote::init();
	phx::core::actor::rigidactor::remote::init();
	phx::core::actor::rigidstatic::base::init();
}
void			phx::core::actor::rigidstatic::remote::release() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;
	
	//neb::core::actor::rigidstatic::base::releaseUp();
	neb::core::actor::base::releaseUp();
	
	//neb::core::actor::rigidstatic::remote::releaseUp();
	
	//phx::core::actor::rigidstatic::base::releaseUp();
	phx::core::actor::actor::base::releaseUp();
	
	//phx::core::actor::rigidstatic::remote::releaseUp();

}
void			phx::core::actor::rigidstatic::remote::step(gal::std::timestep const & ts) {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;

	neb::core::actor::rigidstatic::remote::step(ts);
	phx::core::actor::rigidactor::remote::step(ts);
	phx::core::actor::rigidstatic::base::step(ts);

}





