#include <Nebula/Shape/Box.hh>

physx::PxGeometry*		Neb::Shape::Box::to_geo() {
	//NEBULA_DEBUG_0_FUNCTION;

	physx::PxGeometry* geo = NULL;

	physx::PxVec3 s = raw_->s_;

	geo = new physx::PxBoxGeometry(s * 0.5);

	return geo;
}
