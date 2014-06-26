
#include <PhysX/util/convert.hpp>
#include <PhysX/core/shape/box.hpp>
#include <PhysX/core/actor/rigidactor/base.hpp>

phx::core::shape::box::box(sp::shared_ptr<phx::core::actor::rigidactor::base> parent):
	neb::core::shape::base(parent),
	phx::core::shape::base(parent)
{
}
physx::PxGeometry*		phx::core::shape::box::to_geo() {
	return new physx::PxBoxGeometry(phx::util::convert(s_ * 0.5f));
}


