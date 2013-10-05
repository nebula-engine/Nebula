#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_PHYSX_RIGID_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_PHYSX_RIGID_ACTOR_HPP__


#include <nebula/content/actor/physics/rigid_actor.hpp>
#include <nebula/content/actor/physics/physx/actor.hpp>

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
				class rigid_actor:
					virtual public nebula::content::actor::physics::physx::actor,
					virtual public nebula::content::actor::physics::rigid_actor
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
					virtual	void								init( boost::shared_ptr<nebula::content::actor::admin::base>& );
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step();
					/// render
					virtual	void								render(const boost::shared_ptr<nebula::platform::renderer::base>&);
				
				
				
				
					/// create shapes
					virtual	void								create_shape();

				};
			}
			}
		}
	}
}

#endif








