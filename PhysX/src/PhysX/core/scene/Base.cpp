#include <stdio.h>

#include <Galaxy-Log/log.hpp>

#include <PhysX/app/base.hpp>
#include <PhysX/core/scene/base.hpp>
#include <PhysX/util/convert.hpp>

#include <neb/debug.hh>
#include <neb/core/scene/Util/Types.hh>



phx::core::scene::base::base(sp::shared_ptr< ::neb::core::scene::util::parent > parent):
	neb::core::scene::base(parent),
	px_scene_(NULL)
{
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core scene", debug) << __PRETTY_FUNCTION__;
}
phx::core::scene::base::~base() {

	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core scene", debug) << __PRETTY_FUNCTION__;
}
void			phx::core::scene::base::init() {
	
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core scene", debug) << __PRETTY_FUNCTION__;
	
	neb::core::scene::base::init();
	
	create_physics();
}
void			phx::core::scene::base::release() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core scene", debug) << __PRETTY_FUNCTION__;
}
void			phx::core::scene::base::create_physics() {
	if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core scene", debug) << __PRETTY_FUNCTION__;
	
	if(px_scene_ != NULL) {
		if(DEBUG_NEB) BOOST_LOG_CHANNEL_SEV(lg, "phx core scene", debug) << "been here!";
		return;
	}

	auto pxphysics = phx::app::base::global()->px_physics_;
	
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
void		phx::core::scene::base::step(gal::std::timestep const & ts) {
	//NEBULA_DEBUG_1_FUNCTION;

	
	// extras
	//printf("desc size = %i\n", (int)desc_size());
}
sp::weak_ptr<neb::core::actor::rigidstatic::base>		neb::gfx::core::scene::base::createActorRigidStaticCube(neb::core::pose const & pose, real size) {

	auto actor = createActorRigidStaticUninitialized().lock();

	// set data members

	actor->pose_ = pose;

	// initialize (create physx)

	actor->init();

	// create shape

	auto shape = actor->createShapeCube(size);

	// reinitialize in order to apply filtering to shape
	/** @todo consider implementing refresh-type function instead */
	actor->init();

	return actor;
}
/*sp::weak_ptr<neb::core::actor::rigiddynamic::base>		neb::core::scene::base::createActorRigidDynamicCube(neb::core::pose const & pose, real size) {

  auto actor = createActorRigidDynamicUninitialized().lock();

// set data members

actor->pose_ = pose;

// initialize (create physx)

actor->init();

// create shape

auto shape = actor->createShapeCube(size);

// reinitialize in order to apply filtering to shape
 ** @todo consider implementing refresh-type function instead *
 actor->init();

 return actor;











 sp::shared_ptr<phx::core::actor::rigiddynamic::local>		create_actor_dynamic(sp::shared_ptr<phx::core::scene::local> scene) {

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




}*/
sp::weak_ptr<neb::core::actor::base>				neb::gfx::core::scene::base::createActorLightPoint(vec3 p) {

	auto self(isSceneBase());

	auto actor = sp::make_shared<neb::core::actor::base>(self);

	insert(actor);

	actor->init();

	// shape	
	/*
	   auto shape = sp::make_shared<neb::core::shape::empty>(actor);

	   actor->neb::core::shape::util::parent::insert(shape);

	   shape->init();
	 */
	auto shape = actor->neb::core::shape::util::parent::cii< neb::core::shape::empty, sp::shared_ptr<neb::core::actor::empty> >(actor);

	// light
	auto light = sp::make_shared<neb::core::light::Point>(shape);

	shape->neb::core::light::util::parent::insert(light);

	light->init();

	return actor;	
}




