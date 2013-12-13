#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__

#include <PxPhysicsAPI.h>

#include <glutpp/object.h>

#include <neb/actor/Base.h>

namespace neb
{
	namespace actor
	{
		class Actor:
			public neb::actor::Base
		{
			public:
				Actor();
				virtual void		init() = 0;
				virtual void		add_force() = 0;
				virtual void		set_pose(math::transform);
					
				physx::PxActor*		px_actor_;
				glutpp::object*		object_;
		};
	}
}

#endif








