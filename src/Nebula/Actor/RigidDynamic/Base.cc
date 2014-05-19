#include <Nebula/debug.hh>
#include <Nebula/Shape/Base.hh>
#include <Nebula/physics.hh>
#include <Nebula/Actor/RigidDynamic/Base.hh>

Neb::Actor::RigidDynamic::Base::Base() {
}
Neb::Actor::RigidDynamic::Base::Base(Neb::Actor::Util::Parent_s parent):
	Neb::Actor::RigidBody::Base(parent)
{
	NEBULA_ACTOR_BASE_FUNC;
}
void		Neb::Actor::RigidDynamic::Base::init() {
	NEBULA_ACTOR_BASE_FUNC;

	Neb::Actor::RigidBody::Base::init();
	
	auto pxrd = px_actor_->isRigidDynamic();
	pxrd->setLinearDamping(0.01);
}
void Neb::Actor::RigidDynamic::Base::create_physics() {
	NEBULA_ACTOR_BASE_FUNC;

	assert(px_actor_ == NULL);

	auto scene = getScene();

	physx::PxTransform pose(getPose());


	// PxActor
	physx::PxRigidDynamic* px_rigid_dynamic = 
		Neb::__physics.px_physics_->createRigidDynamic(pose);

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
void Neb::Actor::RigidDynamic::Base::init_physics() {
	NEBULA_ACTOR_BASE_FUNC;
	
	physx::PxRigidDynamic* px_rigid_dynamic = px_actor_->isRigidDynamic();
	
	physx::PxRigidBodyExt::updateMassAndInertia(*px_rigid_dynamic, density_);
	
	setupFiltering();
}




