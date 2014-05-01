#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_STATIC_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_STATIC_HPP__

#include <nebula/actor/Rigid_Actor.hpp>

namespace neb {
	namespace Actor {
		class Rigid_Static: public neb::Actor::RigidActor {
			public:
				Rigid_Static(boost::shared_ptr<glutpp::actor::parent> parent);

				virtual void	init(boost::shared_ptr<glutpp::actor::desc>);

				virtual void	create_physics();
				virtual void	init_physics();
				
				virtual void	step_local(double);
				virtual void	step_remote(double);
		};
	}
}

#endif


