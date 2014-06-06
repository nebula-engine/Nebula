#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__

#include <PxPhysicsAPI.h>


#include <Nebula/Actor/Base.hh>

namespace Neb {
	namespace Actor {
		namespace Actor {
			class PhysX: virtual public Neb::Actor::Actor::Base {
				public:
					Base();
					Base(Neb::Actor::Util::Parent_s);
					
					virtual void			init();
					virtual void			release();
					virtual void			step(Neb::Core::TimeStep const & ts);
					
					virtual void					add_force(real) = 0;
					virtual void					set_pose(physx::PxTransform);
					virtual int					fire();

					virtual sp::shared_ptr<Neb::Actor::Base>	get_projectile() = 0;
					
					virtual void					create_physics() = 0;
					virtual void					init_physics() = 0;

					physx::PxActor*					px_actor_;

					//std::shared_ptr<Neb::actor>		object_;
			};
		}
	}
}

#endif


