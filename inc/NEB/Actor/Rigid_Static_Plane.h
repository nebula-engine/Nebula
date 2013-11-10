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
					public:
						friend class n36000::base;
					protected:
						/// copy ctor
						rigid_static_plane( rigid_static_plane const & ) = default;
						/// assignment
						rigid_static_plane&						operator=( rigid_static_plane const & ) = default;
						/// ctor
						rigid_static_plane( std::shared_ptr<n34100::base> );
					public:
						/// dtor
						~rigid_static_plane();
						/// init
						virtual	void							init();
						/// shutdown
						virtual	void							shutdown();
						/// update
						virtual	void							update();
						/// step
						virtual	void							step( float );
						/// render
						virtual	void							render( std::shared_ptr<n23000::base> );
				};
			}
		}
	}
}


#endif








