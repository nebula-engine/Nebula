
#include <neb/fnd/core/shape/base.hpp>

#include <neb/phx/core/shape/box.hpp>
//#include <neb/phx/core/actor/rigidactor/base.hpp>

typedef neb::phx::core::shape::box THIS;

THIS::box()
{
}
void				THIS::init(parent_t * const & p)
{
	printv_func(DEBUG);

	create_physics();
}
void				THIS::release()
{
}
void				THIS::step(gal::etc::timestep const & ts)
{
}
physx::PxGeometry*		THIS::to_geo()
{
	auto p = getParent();
	
	return new physx::PxBoxGeometry(
			p->scale_[0] * 0.5f,
			p->scale_[1] * 0.5f,
			p->scale_[2] * 0.5f
			);
}



