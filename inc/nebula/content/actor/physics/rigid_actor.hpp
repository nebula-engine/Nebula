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
					virtual	void								init( jess::shared_ptr<nebula::content::actor::admin::base> );
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








