#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__

#include <PxPhysicsAPI.h>

#include <neb/actor/Base.h>

namespace neb
{
	namespace actor
	{
		class Actor:
			public neb::actor::Base
		{
			public:
				virtual void		init() = 0;

				physx::PxActor*		px_actor_;

		};
	}
}

#endif








