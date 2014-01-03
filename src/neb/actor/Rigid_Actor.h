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
						glutpp::actor::desc*,
						std::shared_ptr<neb::scene::scene>,
						neb::actor::Base_shared = neb::actor::Base_shared());

				virtual void			init();
				virtual void			add_force() {abort();}

				virtual void			step_remote(double);
				virtual void			setupFiltering();

				virtual glutpp::actor::desc*	get_projectile();
				virtual glutpp::actor::desc*	get_desc();
				
				virtual void			create_physics() {abort();}
				virtual void			init_physics() {abort();}
		};
	}
}

#endif








