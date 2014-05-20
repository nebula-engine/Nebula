#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_HPP__

#include <PxPhysicsAPI.h>

#include <Nebula/Actor/Base.hh>

namespace Neb {
	namespace Actor {
		namespace Actor {
			class Base: virtual public Neb::Actor::Base {
				public:
					Base();
					Base(Neb::Actor::Util::Parent_s);
					
					template<class D, typename... Args> inline void	dispatch(Args... a) {
						D::visit(this, a...);
					}
					
					virtual void			init(/*Neb::weak_ptr<Neb::Actor::desc>*/);

					virtual void			release();
					virtual void			add_force(double) {abort();}
					virtual void			set_pose(physx::PxTransform);
					virtual int			fire();

					virtual Neb::Actor::Base_s	get_projectile() = 0;

					
					virtual void			create_physics() {abort();}
					virtual void			init_physics() {abort();}

					virtual void			step(double const & time, double const & dt);

					physx::PxActor*			px_actor_;

					//std::shared_ptr<Neb::actor>		object_;
			};
		}
	}
}

#endif


