#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_ACTOR_HPP__

#include <jess/map.hpp>
#include <jess/shared_ptr.hpp>

#include <nebula/utilities/types/content/actor/types.hpp>
#include <nebula/utilities/types/content/shape/types.hpp>

#include <nebula/content/actor/admin/actor.hpp>

#include <nebula/ns.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace admin
			{
				/// rigid dynamic
				class rigid_actor:
					public ncaa::actor
				{
				public:
					///@name ctor and dtor
					///@{
					// Ctor
					rigid_actor();
					/// Copy Ctor
					rigid_actor(const rigid_actor&);
					/// Dtor
					~rigid_actor();
					///@}

					///@name operator
					///@{
					/// assignment
					rigid_actor&								operator=(const rigid_actor&);
					///@}

				

					/// init
					virtual	void								init( jess::shared_ptr<nebula::content::scene::admin::base> );
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step();
					/// render
					virtual	void								render( jess::shared_ptr<nebula::platform::renderer::base> );
				
				
				
				
					/// create shapes
					virtual	void								create_shape();
					/// create box
					virtual jess::shared_ptr<ncsa::box>					create_box();
					
					/// shapes
					jess::map<ncsa::base>							shapes_;
				};
			}
		}
	}
}

#endif








