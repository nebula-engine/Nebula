#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_BODY_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_BODY_HPP__



#include <nebula/content/actor/admin/rigid_actor.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace admin
			{
				/// rigid dynamic
				class rigid_body:
					public nebula::content::actor::admin::rigid_actor
				{
					protected:
						/// copy ctor
						rigid_body( rigid_body const & __actor__ ):
							rigid_actor( __actor__ )
					{

					}
						/// assignment
						rigid_body&								operator=(const rigid_body&)
						{
							return *this;
						}
					public:
						// ctor
						rigid_body( jess::shared_ptr<n32100::base> );
						/// dtor
						~rigid_body();
						/// init
						virtual	void								init();
						/// shutdown
						virtual	void								shutdown();
						/// update
						virtual	void								update();
						/// step
						virtual	void								step(float);
						/// render
						virtual	void								render( jess::shared_ptr<nebula::platform::renderer::base> );
						/// create shape
						virtual void								create_shapes();
				};
			}
		}
	}
}

#endif








