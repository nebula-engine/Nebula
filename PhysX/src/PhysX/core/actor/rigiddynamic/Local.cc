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
void				phx::core::actor::rigiddynamic::local::add_force(real) {
}
void				phx::core::actor::rigiddynamic::local::create_physics() {
}
void				phx::core::actor::rigiddynamic::local::init_physics() {
}
void				phx::core::actor::rigiddynamic::local::setPose(neb::core::pose const & pose) {
	
}
sp::shared_ptr<phx::core::actor::rigiddynamic::local>		phx::core::actor::rigiddynamic::local::get_projectile() {
	return phx::core::actor::rigidbody::base::get_projectile();
}


