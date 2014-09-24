#include <stdio.h>

#include <neb/core/math/geo/polyhedron.hh>

math::geo::cuboid::cuboid(float x, float y, float z) {


	polygons_.push_back(make_shared<math::geo::rectangle>(glm::vec3(-x*0.5, 0, 0), glm::vec3( 0, 1, 0), glm::vec3(-1, 0, 0), y, z));
	polygons_.push_back(make_shared<math::geo::rectangle>(glm::vec3( x*0.5, 0, 0), glm::vec3( 0, 1, 0), glm::vec3( 1, 0, 0), y, z));

	polygons_.push_back(make_shared<math::geo::rectangle>(glm::vec3( 0,-y*0.5, 0), glm::vec3( 0, 0, 1), glm::vec3( 0,-1, 0), x, z));
	polygons_.push_back(make_shared<math::geo::rectangle>(glm::vec3( 0, y*0.5, 0), glm::vec3( 0, 0, 1), glm::vec3( 0, 1, 0), x, z));

	polygons_.push_back(make_shared<math::geo::rectangle>(glm::vec3( 0, 0,-z*0.5), glm::vec3( 1, 0, 0), glm::vec3( 0, 0,-1), x, y));
	polygons_.push_back(make_shared<math::geo::rectangle>(glm::vec3( 0, 0, z*0.5), glm::vec3( 1, 0, 0), glm::vec3( 0, 0, 1), x, y));


	
}

