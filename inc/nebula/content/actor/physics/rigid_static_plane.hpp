#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_STATIC_PLANE_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_STATIC_PLANE_HPP__

#include <nebula/content/actor/physics/rigid_static.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace physics
			{
				/// rigid dynamic
				class rigid_static_plane:
					public n34200::rigid_static
				{
					protected:
						// ctor
						rigid_static_plane()
						{

						}
						/// copy ctor
						rigid_static_plane( rigid_static_plane const & )
						{

						}
						/// dtor
						~rigid_static_plane()
						{

						}
						/// assignment
						rigid_static_plane&							operator=( rigid_static_plane const & )
						{
return *this;
						}
					public:
						/// ctor
						rigid_static_plane( jess::shared_ptr<n34100::base> );
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
						virtual	void								create_shape();
				};
			}
		}
	}
}


#endif








