#include <neb/math/geo/polygon.hpp>

math::geo::tri::tri(std::shared_ptr<vertex> v0, std::shared_ptr<vertex> v1, std::shared_ptr<vertex> v2):
v_({v0,v1,v2})
{
}

