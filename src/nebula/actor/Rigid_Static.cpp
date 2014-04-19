#include <neb/physics.h>
#include <neb/shape.h>
#include <neb/actor/Rigid_Static.h>

neb::actor::Rigid_Static::Rigid_Static(glutpp::parent_s parent):
	neb::actor::Rigid_Actor(parent)
{
	printf("%s\n",__PRETTY_FUNCTION__);
}
void	neb::actor::Rigid_Static::init(glutpp::actor::desc_s desc) {
	printf("%s\n",__PRETTY_FUNCTION__);
	
	neb::actor::Rigid_Actor::init(desc);
}
void	neb::actor::Rigid_Static::step_local(double time) {
	NEBULA_DEBUG_1_FUNCTION;
	neb::actor::Rigid_Actor::step_local(time);
}
void	neb::actor::Rigid_Static::step_remote(double time) {
	NEBULA_DEBUG_1_FUNCTION;
	neb::actor::Rigid_Actor::step_remote(time);
}
void neb::actor::Rigid_Static::create_physics() {

	printf("%s\n", __PRETTY_FUNCTION__);
	
	assert(px_actor_ == NULL);
	
	auto scene = get_scene();//scene_.lock();
	
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


