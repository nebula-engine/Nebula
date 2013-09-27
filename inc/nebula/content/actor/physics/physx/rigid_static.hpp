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
					virtual public ncap::rigid_static,
					virtual public ncapp::rigid_actor
				{
				public:
					/// ctor
					rigid_static();
					/// dtor
					~rigid_static();

					/// Initialize
					virtual	void						init(const boost::shared_ptr<ncaa::base>&);
					/// ShutDown
					virtual	void						shutdown();
					/// Update
					virtual	void						update();
					/// Render
					virtual	void						render(const boost::shared_ptr<nebula::platform::renderer::base>&);
					/// Step
					virtual	void						step(FLOAT dt);
					



					/// Create Shapes
					virtual	void						create_shape();


				};
			}
			}
		}
	}
}


#endif





