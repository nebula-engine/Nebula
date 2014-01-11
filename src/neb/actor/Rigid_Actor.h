#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__

#include <neb/actor/Actor.h>

namespace neb
{
	class shape;
	namespace actor
	{
		class Rigid_Actor:
			public neb::actor::Actor
		{
			public:
				Rigid_Actor(
						neb::scene::scene_s,
						neb::actor::Base_s = neb::actor::Base_s());

				virtual void			init(glutpp::actor::desc_s);
				virtual void			add_force() {abort();}

				virtual void			step_remote(double);
				virtual void			setupFiltering();

				virtual glutpp::actor::desc_s	get_projectile();
				
				virtual void			create_physics() {abort();}
				virtual void			init_physics() {abort();}
		};
	}
}

#endif








