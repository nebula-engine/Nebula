#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_STATIC_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_STATIC_HPP__

#include <Nebula/Actor/Rigid_Actor.hpp>

namespace Neb {
	namespace Actor {
		class Rigid_Static: public Neb::Actor::RigidActor {
			public:
				Rigid_Static(Neb::Actor::parent_w parent);

				virtual void	init(Neb::Actor::desc_w);

				virtual void	create_physics();
				virtual void	init_physics();
				
				virtual void	step_local(double);
				virtual void	step_remote(double);
		};
	}
}

#endif


