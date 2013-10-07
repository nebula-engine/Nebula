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
				public:
					///@name ctor and dtor
					///@{
					// Ctor
					rigid_body();
					/// Copy Ctor
					rigid_body(const rigid_body&);
					/// Dtor
					~rigid_body();
					///@}

					///@name operator
					///@{
					/// assignment
					rigid_body&								operator=(const rigid_body&);
					///@}

				

					/// init
					virtual	void								init( jess::shared_ptr<nebula::content::scene::admin::base> );
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step(FLOAT);
					/// render
					virtual	void								render( jess::shared_ptr<nebula::platform::renderer::base> );
				
				
					virtual void								create_shapes();
				
					
				};
			}
		}
	}
}

#endif








