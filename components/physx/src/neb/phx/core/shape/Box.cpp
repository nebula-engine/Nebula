
#include <neb/phx/util/convert.hpp>
#include <neb/phx/core/shape/box.hpp>
#include <neb/phx/core/actor/rigidactor/base.hpp>

neb::phx::core::shape::box::box(std::shared_ptr<neb::phx::core::shape::util::parent> parent):
	neb::core::core::shape::base(parent),
	neb::phx::core::shape::base(parent)
{
}
physx::PxGeometry*		neb::phx::core::shape::box::to_geo() {
	return new physx::PxBoxGeometry(neb::phx::util::convert(s_ * 0.5f));
}



