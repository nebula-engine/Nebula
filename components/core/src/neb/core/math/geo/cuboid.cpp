#include <stdio.h>

<<<<<<< HEAD
#include <neb/core/math/geo/polyhedron.hh>

math::geo::cuboid::cuboid(float x, float y, float z) {


	polygons_.push_back(make_shared<math::geo::rectangle>(glm::vec3(-x*0.5, 0, 0), glm::vec3( 0, 1, 0), glm::vec3(-1, 0, 0), y, z));
	polygons_.push_back(make_shared<math::geo::rectangle>(glm::vec3( x*0.5, 0, 0), glm::vec3( 0, 1, 0), glm::vec3( 1, 0, 0), y, z));

	polygons_.push_back(make_shared<math::geo::rectangle>(glm::vec3( 0,-y*0.5, 0), glm::vec3( 0, 0, 1), glm::vec3( 0,-1, 0), x, z));
	polygons_.push_back(make_shared<math::geo::rectangle>(glm::vec3( 0, y*0.5, 0), glm::vec3( 0, 0, 1), glm::vec3( 0, 1, 0), x, z));

	polygons_.push_back(make_shared<math::geo::rectangle>(glm::vec3( 0, 0,-z*0.5), glm::vec3( 1, 0, 0), glm::vec3( 0, 0,-1), x, y));
	polygons_.push_back(make_shared<math::geo::rectangle>(glm::vec3( 0, 0, z*0.5), glm::vec3( 1, 0, 0), glm::vec3( 0, 0, 1), x, y));
=======
#include <neb/core/math/geo/polygon.hpp>
#include <neb/core/math/geo/polyhedron.hh>
#include <neb/core/math/geo/quad.hpp>

math::geo::cuboid::cuboid(float x, float y, float z) {
	
	polygons_ = new math::geo::polygon[6];
	nbPolys_ = 6;

	polygons_[0] = math::geo::rectangle(glm::vec3(-x*0.5, 0, 0), glm::vec3( 0, 1, 0), glm::vec3(-1, 0, 0), y, z);
	polygons_[1] = math::geo::rectangle(glm::vec3( x*0.5, 0, 0), glm::vec3( 0, 1, 0), glm::vec3( 1, 0, 0), y, z);
	polygons_[2] = math::geo::rectangle(glm::vec3( 0,-y*0.5, 0), glm::vec3( 0, 0, 1), glm::vec3( 0,-1, 0), x, z);
	polygons_[3] = math::geo::rectangle(glm::vec3( 0, y*0.5, 0), glm::vec3( 0, 0, 1), glm::vec3( 0, 1, 0), x, z);
	polygons_[4] = math::geo::rectangle(glm::vec3( 0, 0,-z*0.5), glm::vec3( 1, 0, 0), glm::vec3( 0, 0,-1), x, y);
	polygons_[5] = math::geo::rectangle(glm::vec3( 0, 0, z*0.5), glm::vec3( 1, 0, 0), glm::vec3( 0, 0, 1), x, y);
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507


	
}

