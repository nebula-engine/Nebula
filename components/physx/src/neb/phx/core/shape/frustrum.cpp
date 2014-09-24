
#include <neb/phx/util/convert.hpp>
#include <neb/phx/core/shape/frustrum.hpp>
#include <neb/phx/test.hpp>

#include <neb/gfx/camera/proj/base.hpp>

neb::phx::core::shape::frustrum::frustrum()
{
}
physx::PxGeometry*		neb::phx::core::shape::frustrum::to_geo() {
	
	auto c = camera_.lock();
	assert(c);

	return neb::frustrum_geometry(c->proj());
	
}



