
#include <neb/phx/core/shape/sphere.hpp>

physx::PxGeometry*		phx::core::shape::sphere::to_geo() {
	return new physx::PxSphereGeometry(s_.x);
}



