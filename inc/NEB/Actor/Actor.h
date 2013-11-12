#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__

#include <PxPhysicsAPI.h>

#include <NEB/Actor/Base.h>

namespace NEB
{
	namespace Actor
	{
		class Actor:
			public NEB::Actor::Base
		{
			public:
				virtual void Display() = 0;

				physx::PxActor*		px_actor_;

		};
	}
}

#endif








