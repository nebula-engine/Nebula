#include <Nebula/Math/geo/polyhedron.hh>
#include <Nebula/Shape/Box.hh>

neb::core::shape::Box::Box(sp::shared_ptr<neb::core::shape::util::parent> parent):
	neb::core::shape::base(parent)
{
}
void neb::core::shape::Box::Box::createMesh() {
	//mesh_.load("cube.obj");
	
	math::geo::cuboid cube(1.0,1.0,1.0);
	
	mesh_.construct(&cube);
}


