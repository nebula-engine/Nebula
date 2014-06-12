#include <Nebula/Math/geo/quad.hpp>

math::geo::rectangle::rectangle(vec3 center, vec3 n, vec3 x, float w, float h) {
	
	vec3 y = glm::cross(n,x);
	
	glm::normalize(x);
	glm::normalize(y);
	glm::normalize(n);
	
	x *= w * 0.5;
	y *= h * 0.5;
	

	auto v0(sp::make_shared<math::geo::vertex>(center - x - y, n, vec2(0,0)));
	auto v1(sp::make_shared<math::geo::vertex>(center + x - y, n, vec2(1,0)));
	auto v2(sp::make_shared<math::geo::vertex>(center + x + y, n, vec2(1,1)));
	auto v3(sp::make_shared<math::geo::vertex>(center - x + y, n, vec2(0,1)));
	
	triangles_.push_back(sp::make_shared<tri>(v0,v1,v2));
	triangles_.push_back(sp::make_shared<tri>(v2,v3,v0));


}

