
#include <PhysX/util/convert.hpp>
#include <PhysX/core/shape/Box.hh>

physx::PxGeometry*		px::core::shape::box::to_geo() {
	return new physx::PxBoxGeometry(px::util::convert(s_ * 0.5f));
}


