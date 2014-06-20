#include <Galaxy-Log/log.hpp>

#include <PhysX/core/actor/util/parent.hpp>
#include <PhysX/core/actor/rigiddynamic/local.hpp>

phx::core::actor::rigiddynamic::local::local(sp::shared_ptr<phx::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::actor::base(parent),
	neb::core::actor::rigidactor::base(parent),
	neb::core::actor::local(parent),
	neb::core::actor::actor::local(parent),
	neb::core::actor::rigidactor::local(parent),
	neb::core::actor::rigidbody::base(parent),
	neb::core::actor::rigidbody::local(parent),
	neb::core::actor::rigiddynamic::base(parent),
	neb::core::actor::rigiddynamic::local(parent),
	phx::core::actor::base(parent),
	phx::core::actor::local(parent),
	phx::core::actor::actor::base(parent),
	phx::core::actor::actor::local(parent),
	phx::core::actor::rigidactor::base(parent),
	phx::core::actor::rigidactor::local(parent),
	phx::core::actor::rigidbody::base(parent),
	phx::core::actor::rigidbody::local(parent),
	phx::core::actor::rigiddynamic::base(parent)
{
}
void				phx::core::actor::rigiddynamic::local::init() {
	neb::core::actor::rigiddynamic::local::init();
	phx::core::actor::rigidbody::local::init();
	phx::core::actor::rigiddynamic::base::init();
}
void				phx::core::actor::rigiddynamic::local::release() {
	neb::core::actor::rigiddynamic::local::release();
	phx::core::actor::rigidbody::local::release();
	phx::core::actor::rigiddynamic::base::release();
}
void				phx::core::actor::rigiddynamic::local::step(neb::core::TimeStep const & ts) {
	neb::core::actor::rigiddynamic::local::step(ts);
	phx::core::actor::rigidbody::local::step(ts);
	phx::core::actor::rigiddynamic::base::step(ts);
}
/*sp::shared_ptr<phx::core::actor::rigiddynamic::base>		phx::core::actor::rigiddynamic::local::get_projectile() {
	return phx::core::actor::base_s();
}*/
void				phx::core::actor::rigiddynamic::local::add_force(real time) {
	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;
	phx::core::actor::rigidbody::base::add_force(time);
}
void				phx::core::actor::rigiddynamic::local::create_physics() {
	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;

	phx::core::actor::rigiddynamic::base::create_physics();
}
void				phx::core::actor::rigiddynamic::local::init_physics() {
	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;

	phx::core::actor::rigiddynamic::base::init_physics();
}
void				phx::core::actor::rigiddynamic::local::setPose(neb::core::pose const & pose) {
	BOOST_LOG_CHANNEL_SEV(lg, "phx core actor", debug) << __PRETTY_FUNCTION__;

	neb::core::actor::rigiddynamic::local::setPose(pose);
	phx::core::actor::rigidbody::local::setPose(pose);
	phx::core::actor::rigiddynamic::base::setPose(pose);

}


