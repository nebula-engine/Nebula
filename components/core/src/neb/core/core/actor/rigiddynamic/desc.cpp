
#include <neb/core/core/scene/base.hpp>
#include <neb/core/core/actor/rigiddynamic/desc.hpp>



neb::core::core::actor::rigiddynamic::desc::desc()
{
}
neb::core::core::actor::rigiddynamic::desc::desc(neb::core::pose npose):
	neb::core::core::actor::rigidbody::desc(npose)
{
}

std::shared_ptr<neb::core::core::actor::base>		neb::core::core::actor::rigiddynamic::desc::visit(
		neb::core::core::scene::base * const scene
		) const
{
	assert(scene);
	return scene->createActorRigidDynamic(this).lock();
}


