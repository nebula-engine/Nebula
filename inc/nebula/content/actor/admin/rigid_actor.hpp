#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_ACTOR_HPP__

#include <jess/map.hpp>
#include <jess/shared_ptr.hpp>

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
					public n34100::actor
				{
					protected:
						/// Copy Ctor
						rigid_actor(const rigid_actor&);
						/// assignment
						rigid_actor&								operator=(const rigid_actor&);
					public:
						// Ctor
						rigid_actor( jess::shared_ptr<n32100::base> );
						/// Dtor
						~rigid_actor();
						/// init
						virtual	void								init();
						/// shutdown
						virtual	void								shutdown();
						/// update
						virtual	void								update();
						/// step
						virtual	void								step( float );
						/// render
						virtual	void								render( jess::shared_ptr<n23000::base> );
						/// create shapes
						virtual	void								create_shapes();
						/// create box
						virtual jess::shared_ptr<n35100::box>					create_box();
						/// create plane
						virtual jess::shared_ptr<n35100::plane>					create_plane();
						/// shapes
						jess::map<n35100::base>							shapes_;
				};
			}
		}
	}
}

#endif








