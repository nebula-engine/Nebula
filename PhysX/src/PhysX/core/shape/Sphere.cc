#include <Nebula/Shape/Sphere.hh>

physx::PxGeometry*		neb::Shape::Sphere::to_geo() {
	return new physx::PxSphereGeometry(s_.x);
}
void				neb::Shape::Sphere::createMesh() {
	mesh_.load("sphere.obj");
}

