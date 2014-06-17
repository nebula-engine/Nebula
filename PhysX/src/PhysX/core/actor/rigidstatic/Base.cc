
#include <Nebula/debug.hh>
//#include <Nebula/Physics.hh>
#include <Nebula/Shape/Base.hh>

#include <PhysX/app/base.hpp>
#include <PhysX/util/convert.hpp>
#include <PhysX/core/actor/util/parent.hpp>
#include <PhysX/core/actor/rigidstatic/base.hpp>
#include <PhysX/core/scene/base.hpp>

phx::core::actor::rigidstatic::base::base(sp::shared_ptr<phx::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::actor::base(parent),
	neb::core::actor::rigidactor::base(parent),
	neb::core::actor::rigidbody::base(parent),
	phx::core::actor::base(parent),
	phx::core::actor::actor::base(parent),
	phx::core::actor::rigidactor::base(parent)
{
	NEBULA_ACTOR_BASE_FUNC
}
void			phx::core::actor::rigidstatic::base::init() {
	NEBULA_ACTOR_BASE_FUNC
}
void			phx::core::actor::rigidstatic::base::step(neb::core::TimeStep const & ts) {
	NEBULA_ACTOR_BASE_FUNC;
}
void			phx::core::actor::rigidstatic::base::create_physics() {
	NEBULA_ACTOR_BASE_FUNC;
	
	assert(px_actor_ == NULL);
	
	auto scene = sp::dynamic_pointer_cast<phx::core::scene::base>(getScene());//scene_.lock();
	assert(scene);
	
	auto p = getPose();

	physx::PxTransform pose(
			phx::util::convert(vec3(p.pos_)),
			phx::util::convert(p.rot_)
			);

	//pose.p.print();
	//pose.q.print();

	// PxActor
	physx::PxRigidStatic* px_rigid_static = phx::app::base::global()->px_physics_->createRigidStatic(pose);

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
void			phx::core::actor::rigidstatic::base::init_physics() {

	printf("%s\n", __PRETTY_FUNCTION__);

	//physx::PxRigidDynamic* px_rigid_dynamic = px_actor_->isRigidDynamic();

	setupFiltering();
}


