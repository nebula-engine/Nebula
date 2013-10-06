#ifndef _CONTENT_PHYSICS_PHYSICS_PHYSX_H
#define _CONTENT_PHYSICS_PHYSICS_PHYSX_H

#include <memory>

#include <nebula/define.hpp>

#include <PxPhysicsAPI.h>

#include <nebula/content/physics/base.hpp>

#include <nebula/ns.hpp>

/// default error callback for %PhysX
class DefaultErrorCallback: public physx::PxErrorCallback
{
	public:
		/// Reports an error code
		void 	reportError( physx::PxErrorCode::Enum code, const char *message, const char *file, int line);
};


namespace nebula
{
	namespace content
	{
		namespace physics
		{
			namespace physx
			{
				/// %Physx Implementation
				class base: public ncp::base
				{
				public:
					/// Constructor
					base() {};
					/// Destructor
					~base() {};
					/// initialize
					void								init(const jess::shared_ptr<nebula::content::base>&);
					/// shutdown
					void								shutdown();
					

					
					///@name Register Objects
					///@{
					/// %CO_SC_AD_Scene
					virtual void							register_scene( jess::shared_ptr<nc_sc_a::base>&);
					/// %RigidDynamic
					virtual void							register_rigid_dynamic( jess::shared_ptr<ncaa::rigid_dynamic>& );
					/// %Controller
					virtual void							register_controller( jess::shared_ptr<ncaa::controller>& );
					///@}
					
					
					
					///@name fetch objects
					///@{
					/// physx physics
					::physx::PxPhysics*						get_px_physics() const { return px_physics_; }
					/// physx controller manager
					::physx::PxControllerManager*					get_px_controller_manager() const { return px_character_controller_manager_; }
					///@}
					
					
				protected:
					///@name PhysX Objects
					///@{
					/***/
					/// physx default error callback
					DefaultErrorCallback 						px_default_error_callback_;
					/// physx default allocator
					::physx::PxDefaultAllocator 					px_default_allocator_callback_;
					/// physx foundation
					::physx::PxFoundation*						px_foundation_;
					/// physx physics
					::physx::PxPhysics*						px_physics_;
					/// physx profile zone manager
					::physx::PxProfileZoneManager*					px_profile_zone_manager_;
					/// physx cooking
					::physx::PxCooking*						px_cooking_;
					/// physx cuda context manager
					::physx::pxtask::CudaContextManager*				px_cuda_context_manager_;
					/// physx controller manager
					::physx::PxControllerManager*					px_character_controller_manager_;
					///@}
				};
			}
		}
	}
}


#endif









