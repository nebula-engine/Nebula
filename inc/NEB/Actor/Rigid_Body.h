#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_HPP__

#include <NEB/Actor/Rigid_Actor.h>

namespace NEB
{
	namespace Actor
	{
		class Rigid_Body:
			public NEB::Actor::Rigid_Actor
		{
			float							density_;
			physx::PxVec3						velocity_;
		};
	}
}

#endif








