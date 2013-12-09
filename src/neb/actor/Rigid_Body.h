#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_BODY_HPP__

#include <neb/actor/Rigid_Actor.h>

namespace neb
{
	namespace actor
	{
		class Rigid_Body:
			public neb::actor::Rigid_Actor
		{
			public:
				virtual void Display() = 0;

				float							density_;
				physx::PxVec3						velocity_;
		};
	}
}

#endif








