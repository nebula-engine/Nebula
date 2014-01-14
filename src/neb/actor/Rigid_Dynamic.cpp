#include <neb/shape.h>
#include <neb/physics.h>
#include <neb/actor/Rigid_Dynamic.h>

neb::actor::Rigid_Dynamic::Rigid_Dynamic(
		std::shared_ptr<neb::scene::scene> scene,
		std::shared_ptr<neb::actor::Base> actor):
	neb::actor::rigid_body::rigid_body(scene, actor) 
{
	NEBULA_DEBUG_0_FUNCTION;
}
void neb::actor::Rigid_Dynamic::init(glutpp::actor::desc_s desc) {
	NEBULA_DEBUG_0_FUNCTION;

	neb::actor::rigid_body::rigid_body::init(desc);
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

	px_rigid_dynamic->setLinearVelocity(raw_.velocity_, true);

	// userData
	px_rigid_dynamic->userData = this;

	// add PxActor to PxScene
	scene->px_scene_->addActor(*px_rigid_dynamic);

}
void neb::actor::Rigid_Dynamic::init_physics() {
	NEBULA_DEBUG_0_FUNCTION;

	physx::PxRigidDynamic* px_rigid_dynamic = px_actor_->isRigidDynamic();

	physx::PxRigidBodyExt::updateMassAndInertia(*px_rigid_dynamic, raw_.density_);

	setupFiltering();
}






