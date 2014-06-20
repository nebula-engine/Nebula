
#include <PhysX/util/convert.hpp>
#include <PhysX/core/shape/box.hpp>
#include <PhysX/core/actor/rigidactor/base.hpp>

phx::core::shape::box::box(sp::shared_ptr<phx::core::actor::rigidactor::base> parent):
	neb::core::shape::base(parent),
	neb::core::shape::box(parent),
	phx::core::shape::base(parent)
{
}
void				phx::core::shape::box::init() {
	neb::core::shape::box::init();
	phx::core::shape::base::init();
}
void				phx::core::shape::box::release() {
	neb::core::shape::box::release();
	phx::core::shape::base::release();
}
void				phx::core::shape::box::step(neb::core::TimeStep  const & ts) {
	neb::core::shape::box::step(ts);
	phx::core::shape::base::step(ts);
}
physx::PxGeometry*		phx::core::shape::box::to_geo() {
	return new physx::PxBoxGeometry(phx::util::convert(s_ * 0.5f));
}


