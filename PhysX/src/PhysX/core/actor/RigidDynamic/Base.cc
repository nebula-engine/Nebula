#include <Nebula/debug.hh>
#include <Nebula/Shape/Base.hh>
#include <Nebula/Physics.hh>
#include <Nebula/Actor/RigidDynamic/Base.hh>

neb::core::actor::rigiddynamic::Base::Base() {
}
neb::core::actor::rigiddynamic::Base::Base(sp::shared_ptr<neb::core::actor::Util::Parent> parent):
	neb::core::actor::rigidbody::Base(parent)
{
	NEBULA_ACTOR_BASE_FUNC;
}
void		neb::core::actor::rigiddynamic::Base::init() {
	NEBULA_ACTOR_BASE_FUNC;

	neb::core::actor::rigidbody::Base::init();
	
	auto pxrd = px_actor_->isRigidDynamic();
	pxrd->setLinearDamping(0.01);
}
void neb::core::actor::rigiddynamic::Base::create_physics() {
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
void neb::core::actor::rigiddynamic::Base::init_physics() {
	NEBULA_ACTOR_BASE_FUNC;
	
	physx::PxRigidDynamic* px_rigid_dynamic = px_actor_->isRigidDynamic();
	
	physx::PxRigidBodyExt::updateMassAndInertia(*px_rigid_dynamic, density_);
	
	setupFiltering();
}




