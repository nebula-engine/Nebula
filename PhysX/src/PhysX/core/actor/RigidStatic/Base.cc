
#include <Nebula/debug.hh>
//#include <Nebula/Physics.hh>
#include <Nebula/Shape/Base.hh>
#include <PhysX/core/actor/rigidstatic/base.hh>

px::core::actor::RigidStatic::base::base() {
}
px::core::actor::RigidStatic::base::base(sp::shared_ptr<neb::core::actor::util::parent> parent):
	neb::core::actor::rigidactor::base(parent)
{
	NEBULA_ACTOR_BASE_FUNC
}
void			px::core::actor::RigidStatic::base::init() {
	NEBULA_ACTOR_BASE_FUNC
}
void			px::core::actor::RigidStatic::base::step(double dt) {
	NEBULA_ACTOR_BASE_FUNC;
}
void			px::core::actor::RigidStatic::base::create_physics() {
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
void			px::core::actor::RigidStatic::base::init_physics() {

	printf("%s\n", __PRETTY_FUNCTION__);
	
	//physx::PxRigidDynamic* px_rigid_dynamic = px_actor_->isRigidDynamic();
	
	setupFiltering();
}


