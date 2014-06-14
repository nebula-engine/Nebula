#include <Nebula/App/Base.hh>
#include <Nebula/Actor/Base.hh>
#include <Nebula/Actor/RigidBody/Base.hh>
#include <Nebula/timer/Actor/Release.hpp>



#include <PhysX/util/convert.hpp>
#include <PhysX/core/scene/Local.hh>
#include <PhysX/core/actor/rigiddynamic/local.hpp>


void            px::core::scene::local::step(neb::core::TimeStep const & ts) {
	
	auto app = neb::App::Base::global();
	
	// timer
	//timer_set_.step(time);
	
	//physx::PxU32 nbPxactor = px_scene_->getNbActors(physx::PxActorTypeSelectionFlag::eRIGID_DYNAMIC);
	
	// PxScene
	assert(px_scene_ != NULL);

	px_scene_->simulate(ts.dt);
	px_scene_->fetchResults(true);

	// retrieve array of actors that moved
	physx::PxU32 nb_active_transforms;
	const physx::PxActiveTransform* active_transforms = px_scene_->getActiveTransforms(nb_active_transforms);

	//printf( "count PxRigidActor:%i count active transform:%i\n", nbPxactor, nb_active_transforms );

	//physx::PxTransform pose;
	physx::PxTransform pose;

	// update each render object with the new transform
	for(physx::PxU32 i = 0; i < nb_active_transforms; ++i) {
		//physx::PxActor* px_actor = active_transforms[i].actor;

		//printf( "actor type = %i\n", px_actor->getType() );

		physx::PxActor* pxactor = active_transforms[i].actor;
		assert(pxactor);
		physx::PxRigidBody* pxrigidbody = pxactor->isRigidBody();


		void* ud = active_transforms[i].userData;
		assert(ud);

		neb::core::actor::Base* pactor = static_cast<neb::core::actor::Base*>(ud);
		auto actor = pactor->isActorBase();
		

		if(actor) {
			pose = active_transforms[i].actor2World;
			actor->setPose(px::util::convert(pose));
			
			if(pxrigidbody != NULL) {
				auto rigidbody = isActorRigidBody();
				//dynamic_cast<neb::core::actor::rigidbody::RigidBody*>(actor);

				assert(rigidbody != NULL);

				physx::PxVec3 v(pxrigidbody->getLinearVelocity());

				rigidbody->velocity_ = px::util::convert(v);

				//v.print();
			}

			actor->flag_.set(neb::core::actor::Util::Flag::E::SHOULD_UPDATE);
		}
	}

	// vehicle
	//physx::PxVec3 g(0,-0.25,0);
	//vehicle_manager_.vehicle_suspension_raycasts(px_scene_);
	//vehicle_manager_.update((float)dt, g);
	
	send_actor_update();
	
}
void		px::core::scene::local::fire(sp::shared_ptr<px::core::actor::base> actor) {

	auto proj = actor->get_projectile();

	//auto me = std::dynamic_pointer_cast<neb::core::actor::actor>(shared_from_this());

	//auto a = create_actor_local(desc);

	/** @todo replace neb::timer::actor::type with inheritance */

	std::shared_ptr<neb::Timer::actor::Base> t(
			new neb::Timer::actor::Release(proj, last_ + 5.0)
			);


}






