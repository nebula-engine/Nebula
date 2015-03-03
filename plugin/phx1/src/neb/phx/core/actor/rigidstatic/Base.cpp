#include <gal/log/log.hpp>

#include <neb/fnd/util/debug.hpp>
#include <neb/fnd/core/shape/base.hpp>
//#include <neb/fnd/core/shape/base.hpp>

#include <neb/phx/app/base.hpp>
#include <neb/phx/util/convert.hpp>
#include <neb/phx/core/actor/util/parent.hpp>
#include <neb/phx/core/actor/rigidstatic/base.hpp>
#include <neb/phx/core/scene/base.hpp>

/*neb::phx::core::actor::rigidstatic::base::base(std::shared_ptr<neb::phx::core::actor::util::parent> parent):
	neb::fnd::core::actor::base(parent),
	neb::phx::core::actor::base(parent),
	neb::phx::core::actor::actor::base(parent),
	neb::phx::core::actor::rigidactor::base(parent)
{
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;
}*/
void			neb::phx::core::actor::rigidstatic::base::create_physics()
{
	printv_func(DEBUG);

	auto parent = getParent();

	if(!neb::fnd::app::Base::is_valid()) return;
	
	if(px_actor_ != NULL) {
		printv(WARNING, "been here!\n");
		return;
	}
	
	//auto scene = dynamic_cast<neb::phx::core::scene::base*>(parent->getScene()->P::get_object());
	auto scene = dynamic_cast<neb::phx::core::scene::base*>(parent->getScene());
	
	auto p = parent->getPose();

	printv(DEBUG, "pos = %16f %16f %16f\n", p.pos_.x, p.pos_.y, p.pos_.z);

	physx::PxTransform pose(neb::phx::util::convert_pose(p));

	//pose.p.print();
	//pose.q.print();

	// PxActor
	auto app = dynamic_cast<neb::phx::app::base*>(parent->get_fnd_app());

	auto pxph = app->px_physics_;
	assert(pxph);
	
	physx::PxRigidStatic* px_rigid_static = pxph->createRigidStatic(pose);
	
	if(px_rigid_static == NULL) {
		printv(CRITICAL, "create actor failed!");
		exit(1);
	}

	px_actor_ = px_rigid_static;

	// userData
	px_rigid_static->userData = is_fnd_actor_base().get();
	assert(this == shared_from_this().get());
	//assert(this == is_fnd_actor_base().get());

	// add PxActor to PxScene
	//scene->create_physics();
	
	assert(scene->px_scene_ != NULL);

	scene->px_scene_->addActor(*px_rigid_static);
}
void			neb::phx::core::actor::rigidstatic::base::init_physics()
{
	printv_func(DEBUG);

	if(!neb::fnd::app::Base::is_valid()) return;

	setupFiltering();
}


