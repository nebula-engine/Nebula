#include <Neb/Scene/Local.hh>


void            Neb::Scene::Local::stepDeriv(double time) {
	
	
	auto app = get_app();
	
	double dt = time - last_;
	last_ = time;
	
	// timer
	//timer_set_.step(time);
	
	//physx::PxU32 nbPxactor = px_scene_->getNbActors(physx::PxActorTypeSelectionFlag::eRIGID_DYNAMIC);
	
	// PxScene
	assert(px_scene_ != NULL);

	px_scene_->simulate(dt);
	px_scene_->fetchResults(true);

	// retrieve array of actors that moved
	physx::PxU32 nb_active_transforms;
	physx::PxActiveTransform* active_transforms = px_scene_->getActiveTransforms(nb_active_transforms);

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

		glutpp::actor::actor* gl_actor = static_cast<glutpp::actor::actor*>(ud);

		neb::Actor::Actor* actor = dynamic_cast<neb::Actor::Actor*>(gl_actor);
		if(actor != NULL)
		{
			pose = active_transforms[i].actor2World;
			actor->set_pose(pose);

			if(pxrigidbody != NULL) {
				neb::Actor::RigidBody::RigidBody* rigidbody =
					dynamic_cast<neb::Actor::RigidBody::RigidBody*>(actor);

				assert(rigidbody != NULL);

				physx::PxVec3 v(pxrigidbody->getLinearVelocity());

				rigidbody->raw_->velocity_ = v;

				//v.print();
			}

			actor->set(glutpp::actor::actor::flag::SHOULD_UPDATE);
		}
	}

	// vehicle
	//physx::PxVec3 g(0,-0.25,0);
	//vehicle_manager_.vehicle_suspension_raycasts(px_scene_);
	//vehicle_manager_.update((float)dt, g);
	
	send_actor_update();
	
}
