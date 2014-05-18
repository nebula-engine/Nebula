#include <Nebula/Shape/Sphere.hh>

physx::PxGeometry*		Neb::Shape::Sphere::to_geo() {
	//NEBULA_DEBUG_0_FUNCTION;

	physx::PxGeometry* geo = NULL;

	physx::PxVec3 s = raw_->s_;

	geo = new physx::PxSphereGeometry(s.x);

	return geo;
}
