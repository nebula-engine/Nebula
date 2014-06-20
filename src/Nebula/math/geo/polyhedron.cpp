#include <Nebula/math/geo/polyhedron.hh>

std::vector< std::shared_ptr< math::geo::tri > >		math::geo::polyhedron::triangles() {
	
	std::vector< std::shared_ptr< tri > > tris;

	for(auto p : polygons_) {
		assert(p);
		tris.insert(tris.end(), p->triangles_.begin(), p->triangles_.end());
	}

	return tris;
}

