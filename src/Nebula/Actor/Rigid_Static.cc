
#include <Nebula/debug.hpp>
#include <Nebula/physics.hpp>
#include <Nebula/shape/shape.hpp>
#include <Nebula/Actor/Rigid_Static.hpp>

Neb::Actor::Rigid_Static::Rigid_Static(Neb::Actor::parent_w parent): Neb::Actor::RigidActor(parent) {
	NEBULA_ACTOR_BASE_FUNC
}
void	Neb::Actor::Rigid_Static::init(Neb::Actor::desc_w desc) {
	NEBULA_ACTOR_BASE_FUNC
	
	Neb::Actor::RigidActor::init(desc);
}
void	Neb::Actor::Rigid_Static::step_local(double time) {
	NEBULA_ACTOR_BASE_FUNC;
	Neb::Actor::RigidActor::step_local(time);
}
void	Neb::Actor::Rigid_Static::step_remote(double time) {
	NEBULA_ACTOR_BASE_FUNC;
	Neb::Actor::RigidActor::step_remote(time);
}
void Neb::Actor::Rigid_Static::create_physics() {

	printf("%s\n", __PRETTY_FUNCTION__);
	
	assert(px_actor_ == NULL);
	
	auto scene = get_scene();//scene_.lock();
	
	physx::PxTransform pose(getPose());

	//pose.p.print();
	//pose.q.print();
	
	// PxActor
	physx::PxRigidStatic* px_rigid_static = Neb::__physics.px_physics_->createRigidStatic(pose);

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
void Neb::Actor::Rigid_Static::init_physics() {

	printf("%s\n", __PRETTY_FUNCTION__);
	
	//physx::PxRigidDynamic* px_rigid_dynamic = px_actor_->isRigidDynamic();
	
	setupFiltering();
}


