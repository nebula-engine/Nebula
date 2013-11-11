#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_BASE_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_BASE_HPP__

#include <PxPhysicsAPI.h>

namespace NEB
{
	namespace Actor
	{
		class Base
		{
public:
			Base();
			virtual void Display() = 0;

			physx::PxTransform pose_;
		};
	}
}


#endif








