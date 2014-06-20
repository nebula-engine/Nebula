#include <Galaxy-Log/log.hpp>

#include <Nebula/debug.hh>
//#include <Nebula/Physics.hh>
#include <Nebula/core/shape/Base.hh>

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
	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;
}
void			phx::core::actor::rigidstatic::remote::init() {
	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;
	
	neb::core::actor::rigidstatic::remote::init();
	phx::core::actor::rigidactor::remote::init();
	phx::core::actor::rigidstatic::base::init();
}
void			phx::core::actor::rigidstatic::remote::release() {
	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;

	neb::core::actor::rigidstatic::remote::release();
	phx::core::actor::rigidactor::remote::release();
	phx::core::actor::rigidstatic::base::release();

}
void			phx::core::actor::rigidstatic::remote::step(neb::core::TimeStep const & ts) {
	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;

	neb::core::actor::rigidstatic::remote::step(ts);
	phx::core::actor::rigidactor::remote::step(ts);
	phx::core::actor::rigidstatic::base::step(ts);

}





