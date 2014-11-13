
#include <neb/phx/core/shape/sphere.hpp>

physx::PxGeometry*		phx::core::shape::sphere::to_geo() {
<<<<<<< HEAD
	return new physx::PxSphereGeometry(s_.x);
=======
	return new physx::PxSphereGeometry(scale_.x);
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
}



