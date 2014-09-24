#include <neb/core/math/geo/polygon.hpp>

math::geo::tri::tri(std::shared_ptr<vertex> v0, std::shared_ptr<vertex> v1, std::shared_ptr<vertex> v2)
{
	v_[0] = v0;
	v_[1] = v1;
	v_[2] = v2;
}

