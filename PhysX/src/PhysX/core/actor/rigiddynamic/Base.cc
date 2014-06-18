
#include <Nebula/debug.hh>
#include <Nebula/Shape/Base.hh>
//#include <Nebula/Physics.hh>

#include <PhysX/app/base.hpp>
#include <PhysX/core/scene/base.hpp>
#include <PhysX/core/actor/util/parent.hpp>
#include <PhysX/core/actor/rigiddynamic/base.hpp>
#include <PhysX/core/actor/rigiddynamic/base.hpp>
#include <PhysX/util/convert.hpp>

phx::core::actor::rigiddynamic::base::base(sp::shared_ptr<phx::core::actor::util::parent> parent):
	neb::core::actor::base(parent),
	neb::core::actor::actor::base(parent),
	neb::core::actor::rigidactor::base(parent),
	neb::core::actor::rigidbody::base(parent),
	neb::core::actor::rigiddynamic::base(parent),
	phx::core::actor::base(parent),
	phx::core::actor::actor::base(parent),
	phx::core::actor::rigidactor::base(parent),
	phx::core::actor::rigidbody::base(parent)
{
	NEBULA_ACTOR_BASE_FUNC;
}
void			phx::core::actor::rigiddynamic::base::init() {
	NEBULA_ACTOR_BASE_FUNC;
	
	phx::core::actor::rigidbody::base::init();
	neb::core::actor::rigiddynamic::base::init();
	
	auto pxrd = px_actor_->isRigidDynamic();
	pxrd->setLinearDamping(0.01);
}
void			phx::core::actor::rigiddynamic::base::release() {
	NEBULA_ACTOR_BASE_FUNC;
	
	phx::core::actor::rigidbody::base::release();
	neb::core::actor::rigiddynamic::base::release();
	
}
void			phx::core::actor::rigiddynamic::base::step(neb::core::TimeStep const & ts) {
	NEBULA_ACTOR_BASE_FUNC;
	
	phx::core::actor::rigidbody::base::step(ts);
	neb::core::actor::rigiddynamic::base::step(ts);
	
}
void			phx::core::actor::rigiddynamic::base::create_physics() {
	NEBULA_ACTOR_BASE_FUNC;

	assert(px_actor_ == NULL);

	auto scene = sp::dynamic_pointer_cast<phx::core::scene::base>(getScene());

	auto p(getPose());	
	physx::PxTransform pose(
			phx::util::convert(vec3(p.pos_)),
			phx::util::convert(p.rot_)
			);
	
	
	// PxActor
	physx::PxRigidDynamic* px_rigid_dynamic = phx::app::base::global()->px_physics_->createRigidDynamic(pose);

	if (!px_rigid_dynamic)
	{
		printf("create shape failed!");
		exit(1);
	}

	px_actor_ = px_rigid_dynamic;

	px_rigid_dynamic->setLinearVelocity(phx::util::convert(velocity_), true);

	// userData
	px_rigid_dynamic->userData = this;

	// add PxActor to PxScene
	scene->px_scene_->addActor(*px_rigid_dynamic);

}
void			phx::core::actor::rigiddynamic::base::init_physics() {
	NEBULA_ACTOR_BASE_FUNC;
	
	physx::PxRigidDynamic* px_rigid_dynamic = px_actor_->isRigidDynamic();
	
	physx::PxRigidBodyExt::updateMassAndInertia(*px_rigid_dynamic, density_);
	
	setupFiltering();
}




