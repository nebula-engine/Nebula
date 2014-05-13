#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__

#include <Nebula/Actor/Actor.hh>

namespace Neb {
	namespace Actor {
		class RigidActor: public Neb::Actor::Actor {
			public:
				RigidActor(Neb::Actor::Util::Parent_s);

				virtual void					init();

				/*virtual void					step_local(double);
				virtual void					step_remote(double);*/
				
				virtual void					setupFiltering();

				virtual Neb::Actor::Base_s			get_projectile() = 0;
				
				virtual void					create_physics() = 0;
				virtual void					init_physics() = 0;

				virtual void					print_info();
		};
	}
}

#endif








