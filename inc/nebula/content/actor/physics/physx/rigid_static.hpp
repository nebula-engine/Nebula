#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_PHYSX_RIGID_STATIC_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_PHYSX_RIGID_STATIC_HPP__

#include <nebula/content/actor/physics/rigid_static.hpp>
#include <nebula/content/actor/physics/physx/rigid_actor.hpp>

#include <nebula/ns.hpp>

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
					/// rigid static
					class rigid_static:
						virtual public n34200::rigid_static,
						virtual public n34200p::rigid_actor
					{
						public:
							/// ctor
							rigid_static();
							/// dtor
							~rigid_static();

							/// Initialize
							virtual	void						init( jess::shared_ptr<n34100::base> );
							/// ShutDown
							virtual	void						shutdown();
							/// Update
							virtual	void						update();
							/// Render
							virtual	void						render( jess::shared_ptr<nebula::platform::renderer::base> );
							/// Step
							virtual	void						step( float dt );




							/// Create Shapes
							virtual	void						create_shape();


					};
				}
			}
		}
	}
}


#endif





