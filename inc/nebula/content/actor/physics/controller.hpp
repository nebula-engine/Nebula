#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_CONTROLLER_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_CONTROLLER_HPP__

#include <nebula/define.hpp>
#include <PxPhysicsAPI.h>

#include <nebula/content/actor/physics/base.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace physics
			{
				/// controller
				class controller:
					virtual public n34200::base
				{
				public:
					///@name ctor and dtor
					///@{
					// Ctor
					controller();
					/// Copy Ctor
					controller(const controller&);
					/// Dtor
					~controller();
					///@}

					///@name operator
					///@{
					/// assignment
					controller&								operator=(const controller&);
					///@}

				

					/// init
					virtual	void								init( jess::shared_ptr<n34100::base> );
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step(float);
				
					virtual void								update_move();
					
					physx::PxController*							get_px_controller();
					void									set_px_controller( ::physx::PxController* );

					/// PxController
					physx::PxController*							px_controller_;
				};
			}
		}
	}
}

#endif








