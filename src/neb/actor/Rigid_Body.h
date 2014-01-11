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
				Rigid_Body(
						neb::scene::scene_s,
						neb::actor::Base_s = neb::actor::Base_s());
				
				virtual void			init(glutpp::actor::desc_s);
				virtual void			add_force();
				virtual int			key_fun(int,int,int,int);

				virtual glutpp::actor::desc_s	get_projectile();

				virtual void			step_remote(double);



				virtual void			create_physics() {abort();}
				
				
				math::vec3			force_;
				math::vec3			torque_;
		};
	}
}

#endif








