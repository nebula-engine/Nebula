#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_HPP__

#include <nebula/actor/Actor.hpp>

namespace neb {
	namespace Actor {
		class RigidActor:
			public neb::Actor::Actor
		{
			public:
				RigidActor(boost::shared_ptr<glutpp::actor::parent>);

				virtual void			init(boost::shared_ptr<glutpp::actor::desc>);
				virtual void			add_force(double) {abort();}

				virtual void			step_local(double);
				virtual void			step_remote(double);
				
				virtual void			setupFiltering();

				virtual boost::shared_ptr<glutpp::actor::desc>		get_projectile();
				
				virtual void			create_physics() {abort();}
				virtual void			init_physics() {abort();}

				virtual void			print_info();
		};
	}
}

#endif








