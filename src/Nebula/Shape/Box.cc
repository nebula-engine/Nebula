#include <Nebula/Math/geo/polyhedron.hh>
#include <Nebula/Shape/Box.hh>

Neb::Shape::Box::Box(sp::shared_ptr<Neb::Shape::Util::Parent> parent):
	Neb::Shape::Base(parent)
{
}
void Neb::Shape::Box::Box::createMesh() {
	//mesh_.load("cube.obj");
	
	math::geo::cuboid cube(1.0,1.0,1.0);
	
	mesh_.construct(&cube);
}


