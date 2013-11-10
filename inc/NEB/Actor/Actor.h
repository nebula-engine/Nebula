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
				physx::PxActor*						px_actor_;

				physx::PxTransform					pose_;
		};
	}
}

#endif








