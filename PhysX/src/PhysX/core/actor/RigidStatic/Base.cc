
#include <Nebula/debug.hh>
#include <Nebula/Physics.hh>
#include <Nebula/Shape/Base.hh>
#include <Nebula/Actor/RigidStatic/Base.hh>

neb::Actor::RigidStatic::Base::Base() {
}
neb::Actor::RigidStatic::Base::Base(sp::shared_ptr<neb::Actor::Util::Parent> parent):
	neb::Actor::RigidActor::Base(parent)
{
	NEBULA_ACTOR_BASE_FUNC
}
void	neb::Actor::RigidStatic::Base::init() {
	NEBULA_ACTOR_BASE_FUNC
}
void	neb::Actor::RigidStatic::Base::step(double dt) {
	NEBULA_ACTOR_BASE_FUNC;
}
void neb::Actor::RigidStatic::Base::create_physics() {
	NEBULA_ACTOR_BASE_FUNC;
	
	assert(px_actor_ == NULL);
	
	auto scene = getScene();//scene_.lock();
	
	physx::PxTransform pose(getPose());

	//pose.p.print();
	//pose.q.print();
	
	// PxActor
	physx::PxRigidStatic* px_rigid_static = neb::Physics::global()->px_physics_->createRigidStatic(pose);

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
void neb::Actor::RigidStatic::Base::init_physics() {

	printf("%s\n", __PRETTY_FUNCTION__);
	
	//physx::PxRigidDynamic* px_rigid_dynamic = px_actor_->isRigidDynamic();
	
	setupFiltering();
}


