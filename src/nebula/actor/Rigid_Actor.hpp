#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__

#include <nebula/actor/Actor.hpp>

namespace neb {
	namespace actor {
		class RigidActor:
			public neb::actor::Actor
		{
			public:
				RigidActor(glutpp::actor::parent_s);

				virtual void			init(glutpp::actor::desc_s);
				virtual void			add_force(double) {abort();}

				virtual void			step_local(double);
				virtual void			step_remote(double);
				
				virtual void			setupFiltering();

				virtual glutpp::actor::desc_s	get_projectile();
				
				virtual void			create_physics() {abort();}
				virtual void			init_physics() {abort();}

				virtual void			print_info();
		};
	}
}

#endif








