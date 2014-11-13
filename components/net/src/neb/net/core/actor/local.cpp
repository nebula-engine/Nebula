#include <PhysX/core/actor/util/parent.hpp>
#include <PhysX/core/actor/local.hpp>

phx::core::actor::local::local(std::shared_ptr<phx::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::local(parent),
	phx::core::actor::base(parent)
{
}
/*void				phx::core::actor::local::release() {
	neb::core::actor::local::release();
	phx::core::actor::base::release();
}*/
void				phx::core::actor::local::init() {
	neb::core::actor::local::init();
	phx::core::actor::base::init();
}
void				phx::core::actor::local::step(gal::etc::timestep const & ts) {
	neb::core::actor::local::step(ts);
	phx::core::actor::base::step(ts);

}








