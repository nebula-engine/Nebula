
#include <nebula/physics.hpp>
#include <nebula/shape.hpp>
#include <nebula/actor/Rigid_Static.hpp>

neb::Actor::Rigid_Static::Rigid_Static(glutpp::actor::parent_s parent):
	neb::Actor::RigidActor(parent)
{
	printf("%s\n",__PRETTY_FUNCTION__);
}
void	neb::Actor::Rigid_Static::init(glutpp::actor::desc_s desc) {
	printf("%s\n",__PRETTY_FUNCTION__);
	
	neb::Actor::RigidActor::init(desc);
}
void	neb::Actor::Rigid_Static::step_local(double time) {
	NEBULA_DEBUG_1_FUNCTION;
	neb::Actor::RigidActor::step_local(time);
}
void	neb::Actor::Rigid_Static::step_remote(double time) {
	NEBULA_DEBUG_1_FUNCTION;
	neb::Actor::RigidActor::step_remote(time);
}
void neb::Actor::Rigid_Static::create_physics() {

	printf("%s\n", __PRETTY_FUNCTION__);
	
	assert(px_actor_ == NULL);
	
	auto scene = get_scene();//scene_.lock();
	
	math::transform pose(getPose());
	
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
void neb::Actor::Rigid_Static::init_physics() {

	printf("%s\n", __PRETTY_FUNCTION__);
	
	//physx::PxRigidDynamic* px_rigid_dynamic = px_actor_->isRigidDynamic();
	
	setupFiltering();
}


