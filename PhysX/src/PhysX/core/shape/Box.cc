#include <Nebula/Shape/Box.hh>

physx::PxGeometry*		neb::Shape::Box::to_geo() {
	return new physx::PxBoxGeometry(s_ * 0.5);
}
void neb::Shape::Box::Box::createMesh() {
	mesh_.load("cube.obj");
}


