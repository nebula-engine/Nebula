#include <gal/log/log.hpp>

#include <neb/fnd/util/debug.hpp>
#include <neb/fnd/core/shape/base.hpp>

#include <neb/phx/app/base.hpp>
#include <neb/phx/core/scene/base.hpp>
#include <neb/phx/core/actor/util/parent.hpp>
#include <neb/phx/core/actor/rigiddynamic/base.hpp>
#include <neb/phx/util/convert.hpp>


void			neb::phx::core::actor::rigiddynamic::base::init(parent_t * const & p)
{
	printv_func(DEBUG);
	
	assert(px_actor_);
	auto pxrd = px_actor_->isRigidDynamic();
	assert(pxrd);
	pxrd->setLinearDamping(0.01);
}
void			neb::phx::core::actor::rigiddynamic::base::create_physics()
{
	printv_func(DEBUG);

	auto parent = getParent();

	if(px_actor_ != NULL) {
		printv(DEBUG, "been here!\n");
		return;
	}
	
	if(!neb::fnd::app::Base::is_valid()) return;

	auto fnd_scene = parent->getScene();
	//auto scene = dynamic_cast<neb::phx::core::scene::base*>(fnd_scene->P::get_object());
	auto scene = dynamic_cast<neb::phx::core::scene::base*>(fnd_scene);
	
	auto p(parent->getPose());	
	physx::PxTransform pose(
			phx::util::convert(glm::vec3(p.pos_)),
			phx::util::convert(p.rot_)
			);
	
	// PxActor
	auto app = dynamic_cast<neb::phx::app::base*>(parent->get_fnd_app());
	assert(app);

	physx::PxRigidDynamic* px_rigid_dynamic = app->px_physics_->createRigidDynamic(pose);

	if (!px_rigid_dynamic)
	{
		printv(DEBUG, "create actor failed!\n");
		exit(1);
	}

	px_actor_ = px_rigid_dynamic;

	px_rigid_dynamic->setLinearVelocity(neb::phx::util::convert(parent->velocity_), true);

	// userData
	auto sft = shared_from_this();
	auto uc = sft.use_count();

	// set userData to raw neb::fnd::core::actor::base*
	px_rigid_dynamic->userData = is_fnd_actor_base().get();

	// debuggin
	assert(uc == sft.use_count());

	// debug
	//assert(this == shared_from_this().get());
	//assert(this == is_fnd_actor_base().get());
	//assert(this == isPxActorRigidDynamicBase().get());
	//assert(std::dynamic_pointer_cast<neb::phx::core::actor::rigidbody::base>(shared_from_this()));
	

	// add PxActor to PxScene
	assert(scene->px_scene_);
	scene->px_scene_->addActor(*px_rigid_dynamic);

	assert(px_actor_);
}
void			neb::phx::core::actor::rigiddynamic::base::init_physics()
{
	printv_func(DEBUG);

	auto parent = getParent();

	if(!px_actor_) return;

	physx::PxRigidDynamic* px_rigid_dynamic = px_actor_->isRigidDynamic();

	assert(px_rigid_dynamic);

	physx::PxRigidBodyExt::updateMassAndInertia(*px_rigid_dynamic, parent->density_);
	
	setupFiltering();
}




