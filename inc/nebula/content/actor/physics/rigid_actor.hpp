#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__


#include <nebula/utilities/types/content/scene/types.hpp>
#include <nebula/utilities/types/platform/types.hpp>
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
					virtual	void								init(const boost::shared_ptr<nebula::content::actor::admin::base>&);
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step(FLOAT);
					/// render
					virtual	void								render(const boost::shared_ptr<nebula::platform::renderer::base>&);
				
				
				
				
					/// create shapes
					virtual	void								create_shape();
				};
			}
		}
	}
}

#endif








