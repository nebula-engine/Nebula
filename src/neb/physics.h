#ifndef __NEB_PHYSICS_H__
#define __NEB_PHYSICS_H__

#include <memory>

#include <PxPhysicsAPI.h>

#include <neb/scene.h>


class DefaultErrorCallback:
	public physx::PxErrorCallback
{
	public:
		void 	reportError( physx::PxErrorCode::Enum code, char const * message, char const * file, int line );
};


namespace neb
{
	struct filter
	{
		enum type: unsigned int
		{
			NONE = 0,
			STATIC = 1 << 0,
			DYNAMIC = 1 << 1,
			PROJECTILE = 1 << 2,
			UNDRIVABLE_SURFACE = 1 << 3,
		};
		
		static physx::PxU32 const RIGID_AGAINST = type::STATIC | type::DYNAMIC;
		
		static physx::PxU32 const DRIVABLE_SURFACE = type::STATIC | type::DYNAMIC;
		
		static physx::PxU32 const COLLISION_FLAG_WHEEL = 0;
		static physx::PxU32 const COLLISION_FLAG_WHEEL_AGAINST = 0;
		static physx::PxU32 const COLLISION_FLAG_CHASSIS = type::DYNAMIC;
		static physx::PxU32 const COLLISION_FLAG_CHASSIS_AGAINST = RIGID_AGAINST;

	};

	class physics
	{
		public:
			physics();
			void						Init();
			void						Shutdown();
			std::shared_ptr<neb::scene>			Create_Scene(tinyxml2::XMLElement*);

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
