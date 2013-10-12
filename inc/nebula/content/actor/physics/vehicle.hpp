#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_VEHICLE_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_VEHICLE_HPP__



#include <nebula/content/actor/physics/base.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace physics
			{
				/// rigid dynamic
				class vehicle:
					public n34200::base
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
					virtual	void								init( jess::shared_ptr<n34100::base> );
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


#endif








