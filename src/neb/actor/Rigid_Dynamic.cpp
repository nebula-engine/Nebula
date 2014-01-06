#include <neb/shape.h>
#include <neb/physics.h>
#include <neb/actor/Rigid_Dynamic.h>

neb::actor::Rigid_Dynamic::Rigid_Dynamic(
		glutpp::actor::desc_shared desc,
		std::shared_ptr<neb::scene::scene> scene,
		std::shared_ptr<neb::actor::Base> actor):
	neb::actor::Rigid_Body(desc, scene, actor)
{
	printf("%s\n", __PRETTY_FUNCTION__);
}
void neb::actor::Rigid_Dynamic::init() {
	
	printf("%s\n", __PRETTY_FUNCTION__);

	neb::actor::Rigid_Body::init();
}
void neb::actor::Rigid_Dynamic::create_physics() {

	printf("%s\n", __PRETTY_FUNCTION__);

	assert(px_actor_ == NULL);
	
	auto scene = get_scene();

	math::transform pose(get_pose());
	
	math::vec3 velocity	= desc_->raw_.velocity_.to_math();
	

	// PxActor
	physx::PxRigidDynamic* px_rigid_dynamic = 
		neb::__physics.px_physics_->createRigidDynamic(pose);

	if (!px_rigid_dynamic)
	{
		printf("create shape failed!");
		exit(1);
	}

	px_actor_ = px_rigid_dynamic;

	px_rigid_dynamic->setLinearVelocity(velocity, true);

	// userData
	px_rigid_dynamic->userData = this;

	// add PxActor to PxScene
	scene->px_scene_->addActor(*px_rigid_dynamic);

}
void neb::actor::Rigid_Dynamic::init_physics() {

	printf("%s\n", __PRETTY_FUNCTION__);
	
	float density = desc_->raw_.density_;
	
	physx::PxRigidDynamic* px_rigid_dynamic = px_actor_->isRigidDynamic();
	
	physx::PxRigidBodyExt::updateMassAndInertia(*px_rigid_dynamic, density);
	
	setupFiltering();
}






