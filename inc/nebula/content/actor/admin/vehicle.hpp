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
					/// copy ctor
					vehicle( vehicle const & );
					/// assignment
					vehicle&								operator=(const vehicle&);
				public:
					/// ctor
					vehicle( jess::shared_ptr<n32100::base> );
					/// ctor
					~vehicle();
					/// init
					virtual	void								init();
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step(float);
					/// render
					virtual	void								render( jess::shared_ptr<n23000::base> );
				};
			}
		}
	}
}


#endif








