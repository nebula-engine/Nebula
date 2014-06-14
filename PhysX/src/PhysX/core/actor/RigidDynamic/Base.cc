
#include <Nebula/debug.hh>
#include <Nebula/Shape/Base.hh>
//#include <Nebula/Physics.hh>
#include <PhysX/core/actor/rigiddynamic/base.hpp>

px::core::actor::rigiddynamic::base::base(sp::shared_ptr<neb::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::rigiddynamic::base(parent),
	px::core::actor::base(parent),
	px::core::actor::actor::base(parent),
	px::core::actor::rigidactor::base(parent),
	px::core::actor::rigidbody::base(parent)
{
	NEBULA_ACTOR_BASE_FUNC;
}
void			px::core::actor::rigiddynamic::base::init() {
	NEBULA_ACTOR_BASE_FUNC;

	neb::core::actor::rigidbody::base::init();
	
	auto pxrd = px_actor_->isRigidDynamic();
	pxrd->setLinearDamping(0.01);
}
void			px::core::actor::rigiddynamic::base::create_physics() {
	NEBULA_ACTOR_BASE_FUNC;

	assert(px_actor_ == NULL);

	auto scene = getScene();

	physx::PxTransform pose(getPose());


	// PxActor
	physx::PxRigidDynamic* px_rigid_dynamic = neb::Physics::global()->px_physics_->createRigidDynamic(pose);

	if (!px_rigid_dynamic)
	{
		printf("create shape failed!");
		exit(1);
	}

	px_actor_ = px_rigid_dynamic;

	px_rigid_dynamic->setLinearVelocity(velocity_, true);

	// userData
	px_rigid_dynamic->userData = this;

	// add PxActor to PxScene
	scene->px_scene_->addActor(*px_rigid_dynamic);

}
void			px::core::actor::rigiddynamic::base::init_physics() {
	NEBULA_ACTOR_BASE_FUNC;
	
	physx::PxRigidDynamic* px_rigid_dynamic = px_actor_->isRigidDynamic();
	
	physx::PxRigidBodyExt::updateMassAndInertia(*px_rigid_dynamic, density_);
	
	setupFiltering();
}




