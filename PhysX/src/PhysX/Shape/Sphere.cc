#include <Nebula/Shape/Sphere.hh>

physx::PxGeometry*		Neb::Shape::Sphere::to_geo() {
	return new physx::PxSphereGeometry(s_.x);
}
void				Neb::Shape::Sphere::createMesh() {
	mesh_.load("sphere.obj");
}

