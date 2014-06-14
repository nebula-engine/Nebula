#include <PhysX/core/shape/Sphere.hh>

physx::PxGeometry*		px::core::shape::sphere::to_geo() {
	return new physx::PxSphereGeometry(s_.x);
}



