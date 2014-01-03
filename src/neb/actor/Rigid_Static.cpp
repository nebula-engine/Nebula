#include <neb/physics.h>
#include <neb/shape.h>
#include <neb/actor/Rigid_Static.h>

neb::actor::Rigid_Static::Rigid_Static(
		glutpp::actor::desc* desc,
		std::shared_ptr<neb::scene::scene> scene,
		std::shared_ptr<neb::actor::Base> actor):
	neb::actor::Rigid_Actor(desc, scene, actor)
{
	printf("%s\n",__PRETTY_FUNCTION__);
}
void	neb::actor::Rigid_Static::init()
{
	printf("%s\n",__PRETTY_FUNCTION__);
	
	neb::actor::Rigid_Actor::init();
}
void	neb::actor::Rigid_Static::add_force() {

}
void neb::actor::Rigid_Static::create_physics() {

	printf("%s\n", __PRETTY_FUNCTION__);
	
	assert(px_actor_ == NULL);
	
	assert(!scene_.expired());
	auto scene = get_scene();//scene_.lock();
	
	assert(desc_);
	
	math::transform pose(get_pose());
	
	// PxActor
	physx::PxRigidStatic* px_rigid_static = neb::__physics.px_physics_->createRigidStatic(pose);

	if(px_rigid_static == NULL)
	{
		printf("create actor failed!");
		exit(1);
	}

	px_actor_ = px_rigid_static;

	// userData
	px_rigid_static->userData = this;

	// add PxActor to PxScene
	assert(scene->px_scene_ != NULL);

	scene->px_scene_->addActor(*px_rigid_static);
}
void neb::actor::Rigid_Static::init_physics() {

	printf("%s\n", __PRETTY_FUNCTION__);
	
	//physx::PxRigidDynamic* px_rigid_dynamic = px_actor_->isRigidDynamic();
	
	setupFiltering();
}


