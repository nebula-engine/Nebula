#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__

#include <neb/actor/Actor.h>

namespace neb
{
	namespace actor
	{
		class Rigid_Actor:
			public neb::actor::Actor
		{
			public:
				virtual void		init() = 0;

				physx::PxShape*		px_shape_;
		};
	}
}

#endif








