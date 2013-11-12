#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__

#include <NEB/Actor/Actor.h>

namespace NEB
{
	namespace Actor
	{
		class Rigid_Actor:
			public NEB::Actor::Actor
		{
			public:
				virtual void Display() = 0;

				physx::PxShape*		px_shape_;
		};
	}
}

#endif








