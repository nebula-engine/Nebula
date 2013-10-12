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
					protected:
						/// copy ctor
						actor( actor const & _actor_ ): base( _actor_ )
						{

						}
						/// assignment
						actor&									operator=(const actor&)
						{
							return *this;
						}
					public:
						/// ctor
						actor( jess::shared_ptr<n34100::base> );
						/// dtor
						~actor();
						/// init
						virtual	void								init();
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








