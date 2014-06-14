
#include <PhysX/core/shape/sphere.hpp>

physx::PxGeometry*		px::core::shape::sphere::to_geo() {
	return new physx::PxSphereGeometry(s_.x);
}



