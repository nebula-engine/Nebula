#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__

#include <Nebula/Actor/Actor.hpp>

namespace Neb {
	namespace Actor {
		class RigidActor: public Neb::Actor::Actor {
			public:
				RigidActor(Neb::weak_ptr<Neb::Actor::parent>);

				virtual void					init(Neb::weak_ptr<Neb::Actor::desc>);
				virtual void					add_force(double) {abort();}

				virtual void					step_local(double);
				virtual void					step_remote(double);
				
				virtual void					setupFiltering();

				virtual Neb::Actor::Base_s			get_projectile() = 0;
				
				virtual void					create_physics() = 0;
				virtual void					init_physics() = 0;

				virtual void					print_info();
		};
	}
}

#endif








