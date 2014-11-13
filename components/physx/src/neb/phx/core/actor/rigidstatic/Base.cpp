#include <gal/log/log.hpp>

#include <neb/core/util/debug.hpp>
#include <neb/core/core/shape/base.hpp>

#include <neb/phx/app/base.hpp>
#include <neb/phx/util/convert.hpp>
#include <neb/phx/util/log.hpp>
#include <neb/phx/core/actor/util/parent.hpp>
#include <neb/phx/core/actor/rigidstatic/base.hpp>
#include <neb/phx/core/scene/base.hpp>

<<<<<<< HEAD
neb::phx::core::actor::rigidstatic::base::base(std::shared_ptr<neb::phx::core::actor::util::parent> parent):
=======
/*neb::phx::core::actor::rigidstatic::base::base(std::shared_ptr<neb::phx::core::actor::util::parent> parent):
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
	neb::core::core::actor::base(parent),
	neb::phx::core::actor::base(parent),
	neb::phx::core::actor::actor::base(parent),
	neb::phx::core::actor::rigidactor::base(parent)
{
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;
<<<<<<< HEAD
}
=======
}*/
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
void			neb::phx::core::actor::rigidstatic::base::create_physics() {
	LOG(lg, neb::phx::core::actor::sl, debug) << __PRETTY_FUNCTION__;
	
	if(px_actor_ != NULL) {
		LOG(lg, neb::phx::core::actor::sl, debug) << "been here!";
		return;
	}
	
<<<<<<< HEAD
	auto scene = std::dynamic_pointer_cast<phx::core::scene::base>(getScene());//scene_.lock();
	assert(scene);
=======
	auto scene = dynamic_cast<neb::phx::core::scene::base*>(getScene());//scene_.lock();
>>>>>>> d0f62233eb8fed722542d3bfcc237575d904a507
	
	auto p = getPose();

	physx::PxTransform pose(
			neb::phx::util::convert(vec3(p.pos_)),
			neb::phx::util::convert(p.rot_)
			);

	//pose.p.print();
	//pose.q.print();

	// PxActor
	auto app = neb::phx::app::base::global();
	auto pxph = app->px_physics_;
	assert(pxph);
	physx::PxRigidStatic* px_rigid_static = pxph->createRigidStatic(pose);

	if(px_rigid_static == NULL) {
		printf("create actor failed!");
		exit(1);
	}

	px_actor_ = px_rigid_static;

	// userData
	px_rigid_static->userData = isActorBase().get();
	assert(this == shared_from_this().get());
	assert(this == isActorBase().get());

	// add PxActor to PxScene
	assert(scene->px_scene_ != NULL);

	scene->px_scene_->addActor(*px_rigid_static);
}
void			neb::phx::core::actor::rigidstatic::base::init_physics() {

	printf("%s\n", __PRETTY_FUNCTION__);

	setupFiltering();
}


