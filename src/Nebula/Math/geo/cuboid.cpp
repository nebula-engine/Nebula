#include <stdio.h>

#include <Nebula/Math/geo/polyhedron.hh>

//math::geo::thin_cyl::cylinder(float 
math::geo::cuboid::cuboid(float x, float y, float z) {
	
	
	polygons_.push_back(sp::make_shared<math::geo::rectangle>(vec3( 0, 0,-z*0.5), vec3( 1, 0, 0), vec3( 0, 0,-1), x, y));
	polygons_.push_back(sp::make_shared<math::geo::rectangle>(vec3( 0, 0, z*0.5), vec3( 1, 0, 0), vec3( 0, 0, 1), x, y));
	polygons_.push_back(sp::make_shared<math::geo::rectangle>(vec3( 0,-y*0.5, 0), vec3( 1, 0, 0), vec3( 0,-1, 0), x, z));
	polygons_.push_back(sp::make_shared<math::geo::rectangle>(vec3( 0, y*0.5, 0), vec3( 1, 0, 0), vec3( 0, 1, 0), x, z));
	polygons_.push_back(sp::make_shared<math::geo::rectangle>(vec3(-x*0.5, 0, 0), vec3( 0, 1, 0), vec3(-1, 0, 0), y, z));
	polygons_.push_back(sp::make_shared<math::geo::rectangle>(vec3( x*0.5, 0, 0), vec3( 0, 1, 0), vec3( 1, 0, 0), y, z));
	
}

