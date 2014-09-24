#include <stdio.h>

#include <gal/log/log.hpp>

#include <neb/core/util/debug.hpp>
#include <neb/core/core/scene/util/decl.hpp>

#include <neb/phx/app/base.hpp>
#include <neb/phx/core/actor/rigidstatic/base.hpp>
#include <neb/phx/core/actor/rigiddynamic/base.hpp>
#include <neb/phx/core/scene/base.hpp>
#include <neb/phx/util/convert.hpp>
#include <neb/phx/util/log.hpp>

neb::phx::core::scene::base::base(std::shared_ptr<neb::core::core::scene::util::parent > parent):
	neb::core::core::scene::base(parent),
	px_scene_(NULL)
{
	LOG(lg, neb::phx::core::scene::sl, debug) << __PRETTY_FUNCTION__;
}
neb::phx::core::scene::base::~base() {

	LOG(lg, neb::phx::core::scene::sl, debug) << __PRETTY_FUNCTION__;
}
void			neb::phx::core::scene::base::init() {
	
	LOG(lg, neb::phx::core::scene::sl, debug) << __PRETTY_FUNCTION__;
	
	neb::core::core::scene::base::init();
	
	create_physics();
}
void			neb::phx::core::scene::base::release() {
	LOG(lg, neb::phx::core::scene::sl, debug) << __PRETTY_FUNCTION__;
}
void			neb::phx::core::scene::base::create_physics() {
	LOG(lg, neb::phx::core::scene::sl, debug) << __PRETTY_FUNCTION__;
	
	if(px_scene_ != NULL) {
		LOG(lg, neb::phx::core::scene::sl, debug) << "been here!";
		return;
	}

	auto pxphysics = neb::phx::app::base::global()->px_physics_;
	
	physx::PxSceneDesc scene_desc(pxphysics->getTolerancesScale());

	scene_desc.gravity = phx::util::convert(gravity_);

	scene_desc.flags |= physx::PxSceneFlag::eENABLE_ACTIVETRANSFORMS;

	int m_nbThreads = 1;

	// cpu dispatcher
	printf("cpu dispatcher\n");
	if( !scene_desc.cpuDispatcher )
	{
		physx::PxDefaultCpuDispatcher* cpuDispatcher =
			::physx::PxDefaultCpuDispatcherCreate( m_nbThreads );

		assert( cpuDispatcher );

		scene_desc.cpuDispatcher = cpuDispatcher;
	}

	// filter shader
	printf("filter shader\n");
	if(!scene_desc.filterShader)
	{
		if(px_filter_shader_)
		{
			scene_desc.filterShader = px_filter_shader_;
		}
		else
		{
			scene_desc.filterShader = DefaultFilterShader;
		}
	}

	// gpu dispatcher
	printf("gpu dispatcher\n");
#ifdef PX_WINDOWS
	if( !scene_desc.gpuDispatcher && m_cudaContextManager )
	{
		sceneDesc.gpuDispatcher = m_cudaContextManager->getGpuDispatcher();
	}
#endif
	assert( scene_desc.isValid() );

	px_scene_ = pxphysics->createScene(scene_desc);
	assert(px_scene_);

	// simulation callback
	phx::simulation_callback* sec = new phx::simulation_callback;

	simulation_callback_ = sec;

	px_scene_->setSimulationEventCallback(sec);
}
void			neb::phx::core::scene::base::step(gal::etc::timestep const & ts) {

	LOG(lg, neb::phx::core::scene::sl, debug) << __PRETTY_FUNCTION__ << " dt = " << ts.dt;

	auto app = phx::app::base::global();

	// timer
	//timer_set_.step(time);

	//physx::PxU32 nbPxactor = px_scene_->getNbActors(physx::PxActorTypeSelectionFlag::eRIGID_DYNAMIC);

	// PxScene
	assert(px_scene_ != NULL);

	typedef neb::core::core::actor::util::parent A;


	//========================================================================
	// lock all actors

	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
			auto actor = std::dynamic_pointer_cast<neb::core::core::actor::base>(it->ptr_);
			assert(actor);
			actor->mutex_.lock();
			LOG(lg, neb::phx::core::scene::sl, debug) << "actor = " << actor.get();
			});

	LOG(lg, neb::phx::core::scene::sl, debug) << "actors locked";
	/*A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
	  auto actor = std::dynamic_pointer_cast<neb::core::core::actor::base>(it->ptr_);
	  assert(actor);
	  LOG(lg, neb::phx::core::scene::sl, debug) << "actor = " << actor.get();
	  });*/

	LOG(lg, neb::phx::core::scene::sl, debug) << "simulate";

	px_scene_->simulate(ts.dt);
	px_scene_->fetchResults(true);

	LOG(lg, neb::phx::core::scene::sl, debug) << "simulation complete";

	// retrieve array of actors that moved
	physx::PxU32 nb_active_transforms;
	const physx::PxActiveTransform* active_transforms = px_scene_->getActiveTransforms(nb_active_transforms);


	LOG(lg, neb::phx::core::scene::sl, debug)
		<< "active transforms: " << nb_active_transforms;

	//physx::PxTransform pose;
	physx::PxTransform pose;

	// update each render object with the new transform
	for(physx::PxU32 i = 0; i < nb_active_transforms; ++i) {
		//physx::PxActor* px_actor = active_transforms[i].actor;

		//printf( "actor type = %i\n", px_actor->getType() );

		physx::PxActor* pxactor = active_transforms[i].actor;
		assert(pxactor);

		void* ud = active_transforms[i].userData;
		assert(ud);

		LOG(lg, neb::phx::core::scene::sl, debug) << "ud = " << ud;

		physx::PxRigidBody* pxrigidbody = pxactor->isRigidBody();


		neb::core::core::actor::base* pactor = static_cast<neb::core::core::actor::base*>(ud);
		auto actor = pactor->isActorBase();
		assert(actor);

		if(actor) {
			pose = active_transforms[i].actor2World;
			actor->setPose(neb::core::pose(
						phx::util::convert(pose.p),
						phx::util::convert(pose.q)
						));

			LOG(lg, neb::phx::core::scene::sl, debug)
				<< ::std::setw(8) << "p"
					<< ::std::setw(8) << pose.p.x
					<< ::std::setw(8) << pose.p.y
					<< ::std::setw(8) << pose.p.z;

			if(pxrigidbody != NULL) {
				auto rigidbody = ::std::dynamic_pointer_cast<phx::core::actor::rigidbody::base>(actor);
				if(!rigidbody) {
					std::cout << typeid(*actor).name() << ::std::endl;
					abort();
				}

				physx::PxVec3 v(pxrigidbody->getLinearVelocity());

				rigidbody->velocity_ = phx::util::convert(v);

				//v.print();
			}

			actor->flag_.set(neb::core::core::actor::util::flag::E::SHOULD_UPDATE);
		}
	}
	// unlock all actors
	A::map_.for_each<0>([&] (A::map_type::iterator<0> it) {
			auto actor = std::dynamic_pointer_cast<neb::core::core::actor::base>(it->ptr_);
			assert(actor);
			actor->mutex_.unlock();
			});
	// vehicle
	//physx::PxVec3 g(0,-0.25,0);
	//vehicle_manager_.vehicle_suspension_raycasts(px_scene_);
	//vehicle_manager_.update((float)dt, g);
	//send_actor_update();
}
/*weak_ptr<neb::core::core::actor::rigidstatic::base>			neb::phx::core::scene::base::createActorRigidStaticCube(
		neb::core::pose pose,
		double size) {
	auto actor = createActorRigidStaticUninitialized().lock();
	actor->pose_ = pose;
	actor->init();
	// shape
	auto shape = actor->createShapeCube(pose, size);
	/// @todo consider implementing refresh-type function instead 
	actor->init();
	return actor;
}*/

/*

   std::shared_ptr<phx::core::actor::rigiddynamic::local>		create_actor_dynamic(std::shared_ptr<phx::core::scene::local> scene) {

   auto actor = sp::make_shared<phx::core::actor::rigiddynamic::local>(scene);

   scene->insert(actor);

   actor->simulation_.word0 = phx::filter::filter::type::DYNAMIC;
   actor->simulation_.word1 = phx::filter::filter::RIGID_AGAINST;

   actor->init();

// shape	
auto shape = sp::make_shared<phx::core::shape::box>(actor);

actor->neb::core::shape::util::parent::insert(shape);

shape->init();

actor->setupFiltering();

std::cout << "actor dynamic use count = " << actor.use_count() << std::endl;

return actor;	
}




}
*/




