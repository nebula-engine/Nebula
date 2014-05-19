
#include <Nebula/debug.hh>
#include <Nebula/physics.hh>
#include <Nebula/Shape/Base.hh>
#include <Nebula/Actor/RigidStatic/Base.hh>

Neb::Actor::RigidStatic::Base::Base() {
}
Neb::Actor::RigidStatic::Base::Base(Neb::Actor::Util::Parent_s parent):
	Neb::Actor::RigidActor::Base(parent)
{
	NEBULA_ACTOR_BASE_FUNC
}
void	Neb::Actor::RigidStatic::Base::init() {
	NEBULA_ACTOR_BASE_FUNC
}
void	Neb::Actor::RigidStatic::Base::step(double dt) {
	NEBULA_ACTOR_BASE_FUNC;
}
void Neb::Actor::RigidStatic::Base::create_physics() {
	NEBULA_ACTOR_BASE_FUNC;
	
	assert(px_actor_ == NULL);
	
	auto scene = getScene();//scene_.lock();
	
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
void Neb::Actor::RigidStatic::Base::init_physics() {

	printf("%s\n", __PRETTY_FUNCTION__);
	
	//physx::PxRigidDynamic* px_rigid_dynamic = px_actor_->isRigidDynamic();
	
	setupFiltering();
}


