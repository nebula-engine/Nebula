#ifndef __NEBULA_CONTENT_ACTOR_RENDERER_VEHICLE_HPP__
#define __NEBULA_CONTENT_ACTOR_RENDERER_VEHICLE_HPP__



#include <nebula/content/actor/admin/base.h>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace renderer
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
					virtual	void								init(const boost::shared_ptr<nebula::content::scene::admin::base>&);
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step();
					/// render
					virtual	void								render(const boost::shared_ptr<nebula::platform::renderer::base>&);
				
				
				
				};
			}
		}
	}
}


#endif








