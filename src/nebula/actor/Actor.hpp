#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__

#include <PxPhysicsAPI.h>

#include <gru/actor/actor.hpp>

#include <nebula/actor/Base.hpp>

namespace neb {
	namespace actor {
		class Actor: public neb::actor::Base {
			public:
				Actor(glutpp::parent_s);


				virtual void			init(glutpp::actor::desc_s);
				virtual void			release();
				virtual void			add_force(double) {abort();}
				virtual void			set_pose(math::transform);
				virtual int			fire();

				virtual glutpp::actor::desc_s	get_projectile() {abort(); return NULL;}
				
				
				virtual void			create_physics() {abort();}
				virtual void			init_physics() {abort();}
				
				
				virtual void			step_local(double);
				virtual void			step_remote(double);

				virtual void			print_info();
				
				physx::PxActor*			px_actor_;
				
				//std::shared_ptr<glutpp::actor>		object_;
		};
	}
}

#endif


