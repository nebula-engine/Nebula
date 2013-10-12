#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__

#include <nebula/define.hpp>
#include <PxPhysicsAPI.h>

#include <nebula/content/actor/physics/base.hpp>

namespace nebula
{
	namespace content
	{
		namespace actor
		{
			namespace physics
			{
				/// actor
				class actor:
					public nebula::content::actor::physics::base
				{
				public:
					///@name ctor and dtor
					///@{
					// Ctor
					actor();
					/// Copy Ctor
					actor(const actor&);
					/// Dtor
					~actor();
					///@}

					///@name operator
					///@{
					/// assignment
					actor&									operator=(const actor&);
					///@}

				

					/// init
					virtual	void								init( jess::shared_ptr<nebula::content::actor::admin::base> );
					/// shutdown
					virtual	void								shutdown();
					/// update
					virtual	void								update();
					/// step
					virtual	void								step();
				
				
				
					/// px actor
					physx::PxActor*								px_actor_;
				};
			}
		}
	}
}

#endif








