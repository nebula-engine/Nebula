#ifndef _CONTENT_PHYSICS_PHYSICS_H
#define _CONTENT_PHYSICS_PHYSICS_H

#include <nebula/define.hpp>
#include <PxPhysicsAPI.h>

#include <ker/module/module.hpp>

#include <nebula/content/actor/physics/rigid_actor.hpp>

#include <nebula/ns.hpp>

/** \brief default error callback for physx
 */
class DefaultErrorCallback:
	public physx::PxErrorCallback
{
	public:
		/** \brief report error
		 */
		void 	reportError( physx::PxErrorCode::Enum code, char const * message, char const * file, int line );
};

namespace nebula
{
	namespace content
	{
		namespace physics
		{
			/** \brief physics for app
			 *
			 * -custom fun30000tionality
			 *     -drag-lift
			 *
			 * -before buffer swap
			 *     -onTrigger
			 *     -onContact
			 *     -onConstraintBreak
			 * -after buffer swap
			 *     -onSleep
			 *     -onWake
			 * -callbacks that occur for all objects
			 *     -onConstraintBreak
			 *     -onSleep
			 *     -onWake
			 * -callbacks that only occur if filter shader callback flag is set
			 *     -onTrigger
			 *     -onContact
			 */
			class base:
				public ker::module::module
			{
				protected:
					/** \brief copy ctor
					 */
					base( base const & ) = default;
					/** \brief assignment
					 */
					base&							operator=( base const & ) = default;
				public:
					/// ctor
					base( std::shared_ptr<n30000::base> );
					/// dtor
					virtual ~base();
					/** \brief init
					 */
					virtual	void						init();
					/** \brief shutdown
					 */
					virtual	void						shutdown();
					///@name create
					///@{
					/**
					 */
					/** \brief scene
					 */
					std::shared_ptr<n32200::base>				create_scene( std::shared_ptr<n32100::base> );
					/** \brief rigid dynamic
					 */
					std::shared_ptr<n34200::rigid_dynamic>			create_rigid_dynamic(
							std::shared_ptr<n32100::base>,
							std::shared_ptr<n34100::base>
							);
					/** \brief rigid dynamic box
					 */
					std::shared_ptr<n34200::rigid_dynamic_box>		create_rigid_dynamic_box(
							std::shared_ptr<n32100::base>,
							std::shared_ptr<n34100::base>
							);
					/** \brief rigid static plane
					 */
					std::shared_ptr<n34200::rigid_static_plane>		create_rigid_static_plane(
							std::shared_ptr<n32100::base> scene,
							std::shared_ptr<n34100::base> actor
							);
					/** \brief controller
					 */
					std::shared_ptr<n34200::controller>			create_controller(
							std::shared_ptr<n32100::base>,
							std::shared_ptr<n34100::base>
							);
					/** box
					 */
					std::shared_ptr<n35200::box>				create_box( std::shared_ptr<n35100::box> );
					/** box
					 */
					std::shared_ptr<n35200::plane>				create_plane( std::shared_ptr<n35100::plane> );
					/** \brief physics material
					 */
					std::shared_ptr<n34200::material>			request_physics_material();
					/** \brief physics material
					 */
					std::shared_ptr<n34200::material>			create_physics_material();
					///@}
					/** \brief initialize rigid actor
					 */
					void							init_rigid_actor( n34200::rigid_actor::shared_t actor );
				protected:
					/** brief parent
					 */
					std::weak_ptr<n30000::base>				parent_;
					/** \brief default material
					 */
					std::shared_ptr<n34200::material>			default_material_;
					///@name physx
					///@{
					/**
					 */
					/** \brief physx default error callback
					 */
					DefaultErrorCallback 					px_default_error_callback_;
					/** \brief physx default allocator
					 */
					physx::PxDefaultAllocator 				px_default_allocator_callback_;
					/** \brief physx foundation
					 */
					physx::PxFoundation*					px_foundation_;
					/** \brief physx physics
					 */
					physx::PxPhysics*					px_physics_;
					/** \brief physx profile zone manager
					 */
					physx::PxProfileZoneManager*				px_profile_zone_manager_;
					/** \brief physx cooking
					 */
					physx::PxCooking*					px_cooking_;
					/** \brief physx cuda context manager
					 */
					physx::pxtask::CudaContextManager*			px_cuda_context_manager_;
					/** \brief physx controller manager
					 */
					physx::PxControllerManager*				px_character_controller_manager_;
					///@}
			};
		}
	}
}

#endif

