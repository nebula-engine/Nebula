#include <PhysX/core/actor/rigiddynamic/local.hpp>

px::core::actor::rigiddynamic::local::local(sp::shared_ptr<neb::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::local(parent),
	neb::core::actor::actor::local(parent)
{
}
void				px::core::actor::rigiddynamic::local::init() {
}
void				px::core::actor::rigiddynamic::local::step(neb::core::TimeStep const & ts) {
}
sp::shared_ptr<px::core::actor::base>		px::core::actor::rigiddynamic::local::get_projectile() {
	return px::core::actor::base_s();
}
void				px::core::actor::rigiddynamic::local::add_force(double) {
}
void				px::core::actor::rigiddynamic::local::create_physics() {
}
void				px::core::actor::rigiddynamic::local::init_physics() {
}


