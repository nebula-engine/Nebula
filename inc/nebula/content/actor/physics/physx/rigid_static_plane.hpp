#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_PHYSX_RIGID_STATIC_PLANE_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_PHYSX_RIGID_STATIC_PLANE_HPP__

#include <nebula/content/actor/physics/rigid_static_plane.hpp>
#include <nebula/content/actor/physics/physx/rigid_static.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace physics
			{
				namespace physx
				{
					/// rigid dynamic
					class rigid_static_plane:
						virtual public n34200::rigid_static_plane,
						virtual public n34200p::rigid_static
					{
						public:
							///@name ctor and dtor
							///@{
							// Ctor
							rigid_static_plane();
							/// Copy Ctor
							rigid_static_plane(const rigid_static_plane&);
							/// Dtor
							~rigid_static_plane();
							///@}

							///@name operator
							///@{
							/// assignment
							rigid_static_plane&							operator=(const rigid_static_plane&);
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

					};
				}
			}
		}
	}
}

#endif








