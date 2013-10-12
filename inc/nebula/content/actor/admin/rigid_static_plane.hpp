#ifndef __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_STATIC_PLANE_HPP__
#define __NEBULA_CONTENT_ACTOR_ADMIN_RIGID_STATIC_PLANE_HPP__

#include <nebula/content/actor/admin/rigid_static.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace admin
			{
				/// rigid_static_plane
				class rigid_static_plane:
					public nebula::content::actor::admin::rigid_static
				{
					/// copy ctor
					rigid_static_plane(const rigid_static_plane&);
					/// assignment
					rigid_static_plane&							operator=(const rigid_static_plane&);
					public:
					/// ctor
					rigid_static_plane( jess::shared_ptr<n32100::base> );
					/// dtor
					~rigid_static_plane();
					/// init
					virtual	void								init();
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step( float );
					/// render
					virtual	void								render( jess::shared_ptr<nebula::platform::renderer::base> );
					/// create shapes
					virtual	void								create_shapes();
					public:
					/// plane
					jess::shared_ptr<n35100::plane>						plane_;
				};
			}
		}
	}
}


#endif








