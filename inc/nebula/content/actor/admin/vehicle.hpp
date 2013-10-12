#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_VEHICLE_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_VEHICLE_HPP__



#include <nebula/content/actor/admin/base.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace admin
			{
				/// rigid dynamic
				class vehicle:
					public nebula::content::actor::admin::base
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
					virtual	void								init( jess::shared_ptr<nebula::content::scene::admin::base> );
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step(float);
					/// render
					virtual	void								render( jess::shared_ptr<nebula::platform::renderer::base> );
				
				
				
				};
			}
		}
	}
}


#endif








