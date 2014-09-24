<<<<<<< HEAD
=======
#include <neb/core/math/geo/vertex.hpp>
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
#include <neb/core/math/geo/quad.hpp>

math::geo::rectangle::rectangle(glm::vec3 center, glm::vec3 x, glm::vec3 n, float w, float h) {
	
	glm::vec3 y = glm::cross(n,x);
	
	glm::normalize(x);
	glm::normalize(y);
	glm::normalize(n);
	
	x *= w * 0.5;
	y *= h * 0.5;
	
<<<<<<< HEAD
	auto v0(make_shared<math::geo::vertex>(center - x - y, n, glm::vec2(0,0), x, y));
	auto v1(make_shared<math::geo::vertex>(center + x - y, n, glm::vec2(1,0), x, y));
	auto v2(make_shared<math::geo::vertex>(center + x + y, n, glm::vec2(1,1), x, y));
	auto v3(make_shared<math::geo::vertex>(center - x + y, n, glm::vec2(0,1), x, y));
=======
	auto v0 = new math::geo::vertex(center - x - y, n, glm::vec2(0,0), x, y);
	auto v1 = new math::geo::vertex(center + x - y, n, glm::vec2(1,0), x, y);
	auto v2 = new math::geo::vertex(center + x + y, n, glm::vec2(1,1), x, y);
	auto v3 = new math::geo::vertex(center - x + y, n, glm::vec2(0,1), x, y);
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
	
	
	glm::vec3 e1(v1->p - v0->p);
	glm::vec3 e2(v2->p - v1->p);
<<<<<<< HEAD

	glm::vec3 c = glm::cross(e1,e2);

	if(glm::dot(n,c) < 0) {
		triangles_.push_back(make_shared<tri>(v0,v2,v1));
		triangles_.push_back(make_shared<tri>(v2,v0,v3));
	} else {
		triangles_.push_back(make_shared<tri>(v0,v1,v2));
		triangles_.push_back(make_shared<tri>(v2,v3,v0));
=======
	
	glm::vec3 c = glm::cross(e1,e2);
	
	triangles_ = new math::geo::triangle[2];
	nbTriangles_ = 2;

	if(glm::dot(n,c) < 0) {
		triangles_[0] = triangle(v0,v2,v1);
		triangles_[1] = triangle(v2,v0,v3);
	} else {
		triangles_[0] = triangle(v0,v1,v2);
		triangles_[1] = triangle(v2,v3,v0);
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
	}
}



