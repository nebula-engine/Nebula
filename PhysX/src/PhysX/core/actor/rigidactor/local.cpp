#include <Galaxy-Log/log.hpp>

#include <PhysX/core/actor/util/parent.hpp>
#include <PhysX/core/actor/rigidactor/local.hpp>

phx::core::actor::rigidactor::local::local(sp::shared_ptr<phx::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::actor::base(parent),
	neb::core::actor::rigidactor::base(parent),
	neb::core::actor::local(parent),
	neb::core::actor::actor::local(parent),
	neb::core::actor::rigidactor::local(parent),
	phx::core::actor::base(parent),
	phx::core::actor::local(parent),
	phx::core::actor::actor::base(parent),
	phx::core::actor::actor::local(parent),
	phx::core::actor::rigidactor::base(parent)
{
}
void		phx::core::actor::rigidactor::local::init() {
	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;

	neb::core::actor::rigidactor::local::init();
	phx::core::actor::actor::local::init();
	phx::core::actor::rigidactor::base::init();
}
void		phx::core::actor::rigidactor::local::release() {
	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;

	neb::core::actor::rigidactor::base::release();
	phx::core::actor::actor::local::release();
	phx::core::actor::rigidactor::base::release();

}
void		phx::core::actor::rigidactor::local::step(neb::core::TimeStep const & ts) {
	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;
	
	neb::core::actor::rigidactor::base::step(ts);
	phx::core::actor::actor::local::step(ts);
	phx::core::actor::rigidactor::base::step(ts);
}




