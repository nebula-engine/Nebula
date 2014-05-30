#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_STATIC_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_STATIC_HPP__

#include <Nebula/Actor/RigidActor/Base.hh>

namespace Neb {
	namespace Actor {
		namespace RigidStatic {
			class Base: public Neb::Actor::RigidActor::Base {
				public:
					Base();
					Base(Neb::Actor::Util::Parent_s parent);

					template<class D, typename... Args> inline void	dispatch(Args... a) {
						D::visit(this, a...);
					}

					virtual void	init();

					virtual void	create_physics();
					virtual void	init_physics();

					virtual void	step(double);
			};
		}
	}
}

#endif


