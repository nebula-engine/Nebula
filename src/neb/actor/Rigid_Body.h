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
				Rigid_Body();
				virtual void		init() = 0;
				virtual void		add_force();
				virtual int		key_force(int,int,int,math::vec3);
				virtual int		key_torque(int,int,int,math::vec3);

				float			density_;
				physx::PxVec3		velocity_;
				math::vec3		force_;
				math::vec3		torque_;

		};
	}
}

#endif








