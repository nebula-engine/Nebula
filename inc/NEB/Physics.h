#ifndef __NEB_PHYSICS_H__
#define __NEB_PHYSICS_H__

#include <memory>

#include <PxPhysicsAPI.h>

#include <NEB/Scene.h>

class DefaultErrorCallback:
	public physx::PxErrorCallback
{
	public:
		void 	reportError( physx::PxErrorCode::Enum code, char const * message, char const * file, int line );
};


namespace NEB
{
	class Physics
	{
		public:
			void						Init();
			void						Shutdown();
			std::shared_ptr<NEB::Scene>			Create_Scene(TiXmlElement*);
			NEB::Actor::Rigid_Dynamic_Box*			Create_Rigid_Dynamic_Box();

			DefaultErrorCallback 				px_default_error_callback_;
			physx::PxDefaultAllocator 			px_default_allocator_callback_;
			physx::PxFoundation*				px_foundation_;
			physx::PxPhysics*				px_physics_;
			physx::PxProfileZoneManager*			px_profile_zone_manager_;
			physx::PxCooking*				px_cooking_;
			physx::pxtask::CudaContextManager*		px_cuda_context_manager_;
			physx::PxControllerManager*			px_character_controller_manager_;

	};
	
	extern "C" Physics physics;
}


#endif
