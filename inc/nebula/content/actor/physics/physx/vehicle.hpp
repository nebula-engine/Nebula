#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_PHYSX_VEHICLE_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_PHYSX_VEHICLE_HPP__

#include <jess/shared_ptr.hpp>

#include <nebula/content/actor/physics/vehicle.hpp>
#include <nebula/content/actor/physics/physx/base.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace physics
			{
namespace physx
{
				/// rigid dynamic
				class vehicle:
					virtual public ncap::vehicle,
					virtual public ncapp::base
				{
				public:
					///@name ctor and dtor
					///@{
					// Ctor
					vehicle();
					/// Copy Ctor
					vehicle(const vehicle&);
					/// Dtor
					~vehicle();
					///@}

					///@name operator
					///@{
					/// assignment
					vehicle&								operator=(const vehicle&);
					///@}
					
					

					/// init
					virtual	void								init( jess::shared_ptr<ncaa::base> );
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step();
					/// render
					virtual	void								render( jess::shared_ptr<nebula::platform::renderer::base> );
				
				
				
				};
			}
		}
	}
}
}

#endif








