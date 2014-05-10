#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__

#include <PxPhysicsAPI.h>

#include <Nebula/Actor/Base.hpp>

namespace Neb {
	namespace Actor {
		class Actor: public Neb::Actor::Base {
			public:
				Actor(Neb::weak_ptr<Neb::Actor::parent>);

				virtual void			init(Neb::weak_ptr<Neb::Actor::desc>);

				virtual void			release();
				virtual void			add_force(double) {abort();}
				virtual void			set_pose(physx::PxTransform);
				virtual int			fire();

				virtual Neb::Actor::Base_s	get_projectile() = 0;
				
				
				virtual void			create_physics() {abort();}
				virtual void			init_physics() {abort();}
				
				
				virtual void			step_local(double);
				virtual void			step_remote(double);

				virtual void			print_info();
				
				physx::PxActor*			px_actor_;
				
				//std::shared_ptr<Neb::actor>		object_;
		};
	}
}

#endif


