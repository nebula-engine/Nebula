#include <Nebula/Math/geo/polyhedron.hh>
#include <Nebula/Shape/Box.hh>

neb::Shape::Box::Box(sp::shared_ptr<neb::Shape::Util::Parent> parent):
	neb::Shape::Base(parent)
{
}
void neb::Shape::Box::Box::createMesh() {
	//mesh_.load("cube.obj");
	
	math::geo::cuboid cube(1.0,1.0,1.0);
	
	mesh_.construct(&cube);
}


