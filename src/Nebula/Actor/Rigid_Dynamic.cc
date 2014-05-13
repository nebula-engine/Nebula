#include <Nebula/debug.hpp>
#include <Nebula/shape/shape.hpp>
#include <Nebula/physics.hpp>
#include <Nebula/Actor/Rigid_Dynamic.hpp>

Neb::Actor::Rigid_Dynamic::Rigid_Dynamic(Neb::Actor::parent_w parent):
	Neb::Actor::RigidBody::RigidBody(parent)
{
	NEBULA_ACTOR_BASE_FUNC;
}
void		Neb::Actor::Rigid_Dynamic::init(Neb::Actor::desc_w desc) {
	NEBULA_ACTOR_BASE_FUNC;

	Neb::Actor::RigidBody::RigidBody::init(desc);
	
	auto pxrd = px_actor_->isRigidDynamic();
	pxrd->setLinearDamping(0.01);
}
void Neb::Actor::Rigid_Dynamic::create_physics() {
	NEBULA_ACTOR_BASE_FUNC;

	assert(px_actor_ == NULL);

	auto scene = get_scene();

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

	px_rigid_dynamic->setLinearVelocity(raw_->velocity_, true);

	// userData
	px_rigid_dynamic->userData = this;

	// add PxActor to PxScene
	scene->px_scene_->addActor(*px_rigid_dynamic);

}
void Neb::Actor::Rigid_Dynamic::init_physics() {
	NEBULA_ACTOR_BASE_FUNC;
	
	physx::PxRigidDynamic* px_rigid_dynamic = px_actor_->isRigidDynamic();
	
	physx::PxRigidBodyExt::updateMassAndInertia(*px_rigid_dynamic, raw_->density_);
	
	setupFiltering();
}
void Neb::Actor::Rigid_Dynamic::print_info() {
	
	Neb::Actor::RigidBody::RigidBody::print_info();
	
	auto pxrd = px_actor_->isRigidDynamic();
	
	float linear_damping = pxrd->getLinearDamping();
	float angular_damping = pxrd->getAngularDamping();
	float max_angular_velocity = pxrd->getMaxAngularVelocity();
	
	printf("PxRigidDynamic:\n");
	printf("linear damping      = %f\n", linear_damping);
	printf("angular damping     = %f\n", angular_damping);
	printf("max angular damping = %f\n", max_angular_velocity);

	

}




