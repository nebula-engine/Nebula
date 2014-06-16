#include <stdio.h>



#include <PhysX/app/base.hpp>
#include <PhysX/core/scene/Base.hh>
#include <PhysX/util/convert.hpp>

#include <Nebula/Scene/Util/Types.hh>

/*
#include <Nebula/Graphics/Window/Base.hh>
#include <Nebula/Graphics/Context/Base.hh>


#include <Nebula/Scene/Base.hh>
#include <Nebula/Scene/Util/Parent.hh>

#include <Nebula/Actor/Base.hh>

#include <Nebula/Graphics/Light/Base.hh>
#include <Nebula/Graphics/glsl/program.hh>
#include <Nebula/Graphics/Camera/Projection/Perspective.hh>

//#include <math/free.hpp>

#include <Nebula/Actor/Util/Type.hh>
#include <Nebula/Message/Actor/Event/Base.hh>
#include <Nebula/Message/Actor/Create.hh>
#include <Nebula/Message/Actor/Update.hh>
#include <Nebula/Message/Actor/Event/Base.hh>
//#include <Nebula/Network/message.hh>
//#include <Nebula/Util/Typed.hh>
#include <Nebula/Memory/smart_ptr.hh>

#include <Nebula/config.hh> // nebula/config.hpp.in
#include <Nebula/App/Base.hh>

#include <Nebula/simulation_callback.hh>
//#include <Nebula/actor/free.hh>
#include <Nebula/Actor/RigidDynamic/Base.hh>
#include <Nebula/Actor/RigidStatic/Base.hh>
#include <Nebula/Actor/Controller/Base.hh>
//#include <Nebula/actor/vehicle.hh>
#include <Nebula/Actor/empty.hh>
#include <Nebula/Shape/Base.hh>
#include <Nebula/timer/Types.hh>
#include <Nebula/timer/Actor/Release.hpp>
*/

phx::core::scene::base::base(sp::shared_ptr< ::neb::Scene::util::parent > parent):
	neb::Scene::base(parent),
	px_scene_(NULL)
{
	GLUTPP_DEBUG_0_FUNCTION;
}
phx::core::scene::base::~base() {
	GLUTPP_DEBUG_0_FUNCTION;
}
void			phx::core::scene::base::init() {
	GLUTPP_DEBUG_0_FUNCTION;
	
	::neb::Scene::base::init();
	
	create_physics();
}
void			phx::core::scene::base::release() {
	GLUTPP_DEBUG_0_FUNCTION;	
}
void			phx::core::scene::base::create_physics() {
	printf("%s\n",__PRETTY_FUNCTION__);
	
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




