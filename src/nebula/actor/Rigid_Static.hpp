#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_STATIC_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_STATIC_HPP__

#include <nebula/actor/Rigid_Actor.hpp>

namespace neb {
	namespace actor {
		class Rigid_Static: public neb::actor::RigidActor {
			public:
				Rigid_Static(glutpp::actor::parent_s parent);

				virtual void	init(glutpp::actor::desc_s);

				virtual void	create_physics();
				virtual void	init_physics();
				
				virtual void	step_local(double);
				virtual void	step_remote(double);
		};
	}
}

#endif


