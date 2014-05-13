
#include <gru/Math/geo/height_map.hpp>
#include <gru/Math/geo/polyhedron.hpp>


math::geo::height_map::height_map(int nx, int ny) {
	vertices_ = new vertex[(nx+1)*(ny+1)];
	tris_     = new tri[nx*ny*2];
}



