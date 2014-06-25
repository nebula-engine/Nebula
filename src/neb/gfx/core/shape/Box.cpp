
#include <neb/math/geo/polyhedron.hh>
#include <neb/gfx/core/shape/Box.hh>

neb::gfx::core::shape::box::box(sp::shared_ptr<neb::core::shape::util::parent> parent):
	neb::core::shape::base(parent)
{
}
void neb::gfx::core::shape::box::box::createMesh() {
	//mesh_.load("cube.obj");
	
	math::geo::cuboid cube(1.0,1.0,1.0);
	
	mesh_.construct(&cube);
}


