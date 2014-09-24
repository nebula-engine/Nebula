#include <gal/log/log.hpp>

#include <neb/core/util/debug.hpp>
#include <neb/core/core/shape/base.hpp>

#include <neb/phx/app/base.hpp>
#include <neb/phx/core/scene/base.hpp>
#include <neb/phx/core/actor/util/parent.hpp>
#include <neb/phx/core/actor/rigiddynamic/base.hpp>
<<<<<<< HEAD
#include <neb/phx/core/actor/rigiddynamic/base.hpp>
#include <neb/phx/util/convert.hpp>
#include <neb/phx/util/log.hpp>

neb::phx::core::actor::rigiddynamic::base::base(::std::shared_ptr<neb::phx::core::actor::util::parent> parent):
=======
#include <neb/phx/util/convert.hpp>
#include <neb/phx/util/log.hpp>

/*neb::phx::core::actor::rigiddynamic::base::base(::std::shared_ptr<neb::phx::core::actor::util::parent> parent):
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
	neb::core::core::actor::base(parent),
	phx::core::actor::base(parent),
	phx::core::actor::actor::base(parent),
	phx::core::actor::rigidactor::base(parent),
	phx::core::actor::rigidbody::base(parent)
{
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;
<<<<<<< HEAD
}
void			neb::phx::core::actor::rigiddynamic::base::init() {
=======
}*/
void			neb::phx::core::actor::rigiddynamic::base::init(parent_t * const & p)
{
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;
	
	assert(px_actor_);
	auto pxrd = px_actor_->isRigidDynamic();
	assert(pxrd);
	pxrd->setLinearDamping(0.01);
}
void			neb::phx::core::actor::rigiddynamic::base::create_physics() {
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;
	
	if(px_actor_ != NULL) {
		LOG(lg, neb::phx::core::actor::sl, debug) << "been here!";
		return;
	}
<<<<<<< HEAD

	auto scene = std::dynamic_pointer_cast<neb::phx::core::scene::base>(getScene());

=======
	
	if(!neb::core::app::__base::is_valid()) return;

	auto scene = dynamic_cast<neb::phx::core::scene::base*>(getScene());
	
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
	auto p(getPose());	
	physx::PxTransform pose(
			phx::util::convert(vec3(p.pos_)),
			phx::util::convert(p.rot_)
			);
	
	
	// PxActor
	physx::PxRigidDynamic* px_rigid_dynamic = neb::phx::app::base::global()->px_physics_->createRigidDynamic(pose);

	if (!px_rigid_dynamic)
	{
		printf("create actor failed!");
		exit(1);
	}

	px_actor_ = px_rigid_dynamic;

	px_rigid_dynamic->setLinearVelocity(neb::phx::util::convert(velocity_), true);

	// userData
	auto sft = shared_from_this();
	auto uc = sft.use_count();


	px_rigid_dynamic->userData = isActorBase().get();


	assert(uc == sft.use_count());

	// debug
	assert(this == shared_from_this().get());
	assert(this == isActorBase().get());
	assert(this == isPxActorRigidDynamicBase().get());
	assert(std::dynamic_pointer_cast<neb::phx::core::actor::rigidbody::base>(shared_from_this()));
	

	// add PxActor to PxScene
	assert(scene->px_scene_);
	scene->px_scene_->addActor(*px_rigid_dynamic);

	assert(px_actor_);
}
void			neb::phx::core::actor::rigiddynamic::base::init_physics() {
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;

<<<<<<< HEAD
	assert(px_actor_);	
	physx::PxRigidDynamic* px_rigid_dynamic = px_actor_->isRigidDynamic();
=======
	if(!px_actor_) return;

	physx::PxRigidDynamic* px_rigid_dynamic = px_actor_->isRigidDynamic();

>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
	assert(px_rigid_dynamic);

	physx::PxRigidBodyExt::updateMassAndInertia(*px_rigid_dynamic, density_);
	
	setupFiltering();
}




