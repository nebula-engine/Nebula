#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_STATIC_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_STATIC_HPP__

#include <Nebula/Actor/Rigid_Actor.hh>

namespace Neb {
	namespace Actor {
		class Rigid_Static: public Neb::Actor::RigidActor {
			public:
				Rigid_Static(Neb::Actor::Util::Parent_s parent);

				virtual void	init();

				virtual void	create_physics();
				virtual void	init_physics();
				
				virtual void	step_local(double);
				virtual void	step_remote(double);
		};
	}
}

#endif


