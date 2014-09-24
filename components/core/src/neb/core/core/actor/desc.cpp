
#include <neb/core/core/actor/rigidbody/desc.hpp>

void							neb::core::core::actor::desc::release()
{
}
std::shared_ptr<neb::core::core::actor::base>		neb::core::core::actor::desc::visit(
		neb::core::core::scene::base * const scene
		) const
{

	return std::shared_ptr<neb::core::core::actor::base>();

}

std::shared_ptr<neb::core::core::actor::base>		neb::core::core::actor::rigidbody::desc::visit(
		neb::core::core::scene::base * const scene
		) const
{

	return std::shared_ptr<neb::core::core::actor::base>();

}


