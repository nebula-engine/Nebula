
#include <nebula/shape.hpp>
#include <nebula/physics.hpp>
#include <nebula/actor/Rigid_Dynamic.hpp>

neb::actor::Rigid_Dynamic::Rigid_Dynamic(glutpp::parent_s parent):
	neb::actor::rigid_body::rigid_body(parent)
{
	NEBULA_DEBUG_0_FUNCTION;
}
void neb::actor::Rigid_Dynamic::init(glutpp::actor::desc_s desc) {
	NEBULA_DEBUG_0_FUNCTION;

	neb::actor::rigid_body::rigid_body::init(desc);
	
	auto pxrd = px_actor_->isRigidDynamic();
	pxrd->setLinearDamping(0.01);
}
void neb::actor::Rigid_Dynamic::create_physics() {
	NEBULA_DEBUG_0_FUNCTION;

	assert(px_actor_ == NULL);

	auto scene = get_scene();

	math::transform pose(get_pose());


	// PxActor
	physx::PxRigidDynamic* px_rigid_dynamic = 
		neb::__physics.px_physics_->createRigidDynamic(pose);

	if (!px_rigid_dynamic)
	{
		printf("create shape failed!");
		exit(1);
	}

	px_actor_ = px_rigid_dynamic;

	px_rigid_dynamic->setLinearVelocity(get_raw()->velocity_, true);

	// userData
	px_rigid_dynamic->userData = this;

	// add PxActor to PxScene
	scene->px_scene_->addActor(*px_rigid_dynamic);

}
void neb::actor::Rigid_Dynamic::init_physics() {
	NEBULA_DEBUG_0_FUNCTION;
	
	physx::PxRigidDynamic* px_rigid_dynamic = px_actor_->isRigidDynamic();
	
	physx::PxRigidBodyExt::updateMassAndInertia(*px_rigid_dynamic, get_raw()->density_);
	
	setupFiltering();
}
void neb::actor::Rigid_Dynamic::print_info() {
	
	neb::actor::rigid_body::rigid_body::print_info();
	
	auto pxrd = px_actor_->isRigidDynamic();
	
	float linear_damping = pxrd->getLinearDamping();
	float angular_damping = pxrd->getAngularDamping();
	float max_angular_velocity = pxrd->getMaxAngularVelocity();
	
	printf("PxRigidDynamic:\n");
	printf("linear damping      = %f\n", linear_damping);
	printf("angular damping     = %f\n", angular_damping);
	printf("max angular damping = %f\n", max_angular_velocity);

	

}




