#ifndef __NEB_PHYSICS_H__
#define __NEB_PHYSICS_H__

#include <memory>

#include <PxPhysicsAPI.h>

#include <Nebula/config.hh>
//#include <Nebula/scene/desc.hh>
#include <Nebula/Scene/scene.hh>

class DefaultErrorCallback:
	public physx::PxErrorCallback
{
	public:
		void reportError(
				physx::PxErrorCode::Enum code,
				char const * message,
				char const * file,
				int line);
};

physx::PxFilterFlags DefaultFilterShader(
		physx::PxFilterObjectAttributes attributes0,
		physx::PxFilterData filterData0,
		physx::PxFilterObjectAttributes attributes1,
		physx::PxFilterData filterData1,
		physx::PxPairFlags& pairFlags,
		const void* constantBlock,
		physx::PxU32 constantBlockSize );

namespace Neb {
	class physics {
		public:
			physics();
			void						Init();
			void						Shutdown();



			DefaultErrorCallback 				px_default_error_callback_;
			physx::PxDefaultAllocator 			px_default_allocator_callback_;
			physx::PxFoundation*				px_foundation_;
			physx::PxPhysics*				px_physics_;
			physx::PxProfileZoneManager*			px_profile_zone_manager_;
			physx::PxCooking*				px_cooking_;
			physx::pxtask::CudaContextManager*		px_cuda_context_manager_;
			physx::PxControllerManager*			px_character_controller_manager_;

	};

	extern "C" physics __physics;
}


#endif
