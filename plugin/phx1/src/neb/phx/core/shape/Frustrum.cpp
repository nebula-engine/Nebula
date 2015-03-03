#include <neb/phx/core/shape/Frustrum.hpp>
/*
#include <neb/phx/util/convert.hpp>
#include <neb/phx/test.hpp>

#include <neb/fnd/camera/proj/Base.hpp>

#include <neb/fin/core/shape/frustrum.hpp>
#include <neb/fin/app/base.hpp>
*/

typedef neb::phx::core::shape::Frustrum THIS;

void				THIS::init(parent_t * const & parent)
{
	setParent(parent);
}
void				THIS::release()
{
}
void				THIS::step(gal::etc::timestep  const & ts)
{
}
physx::PxGeometry*		THIS::to_geo()
{

	/*
	auto c = camera_.lock();
	assert(c);

	//auto app = get_fin_app();
	
	//return app->frustrum_geometry(c->proj());
	*/


	abort();
	return 0;
}

