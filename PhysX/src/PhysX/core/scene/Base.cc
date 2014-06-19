#include <stdio.h>

#include <Galaxy-Log/log.hpp>

#include <PhysX/app/base.hpp>
#include <PhysX/core/scene/base.hpp>
#include <PhysX/util/convert.hpp>

#include <Nebula/Scene/Util/Types.hh>



phx::core::scene::base::base(sp::shared_ptr< ::neb::core::scene::util::parent > parent):
	neb::core::scene::base(parent),
	px_scene_(NULL)
{
	BOOST_LOG_CHANNEL_SEV(lg, "phx core scene", debug) << __PRETTY_FUNCTION__;
}
phx::core::scene::base::~base() {

	BOOST_LOG_CHANNEL_SEV(lg, "phx core scene", debug) << __PRETTY_FUNCTION__;
}
void			phx::core::scene::base::init() {
	
	BOOST_LOG_CHANNEL_SEV(lg, "phx core scene", debug) << __PRETTY_FUNCTION__;
	
	neb::core::scene::base::init();
	
	create_physics();
}
void			phx::core::scene::base::release() {
	BOOST_LOG_CHANNEL_SEV(lg, "phx core scene", debug) << __PRETTY_FUNCTION__;
}
void			phx::core::scene::base::create_physics() {
	BOOST_LOG_CHANNEL_SEV(lg, "phx core scene", debug) << __PRETTY_FUNCTION__;
	
	if(px_scene_ != NULL) {
		BOOST_LOG_CHANNEL_SEV(lg, "phx core scene", debug) << "been here!";
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
void		phx::core::scene::base::step(neb::core::TimeStep const & ts) {
	//NEBULA_DEBUG_1_FUNCTION;

	
	// extras
	//printf("desc size = %i\n", (int)desc_size());
}




