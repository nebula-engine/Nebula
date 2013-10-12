#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__

#include <nebula/content/actor/physics/actor.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace physics
			{
				/// rigid dynamic
				class rigid_actor:
					virtual public nebula::content::actor::physics::actor
				{
					protected:
						/// copy ctor
						rigid_actor( rigid_actor const & original ): actor( original )
						{
							
						}
						/// assignment
						rigid_actor&								operator=( rigid_actor const & )
						{
							return *this;
						}
					public:
						/// ctor
						rigid_actor( jess::shared_ptr<n34100::base> );
						/// dtor
						~rigid_actor();
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


						/// %box
						jess::shared_ptr<n35200::box>						create_box();

						/// create shapes
						virtual	void								create_shapes();
				};
			}
		}
	}
}

#endif








