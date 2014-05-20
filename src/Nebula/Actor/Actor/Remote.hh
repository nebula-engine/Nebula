#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_REMOTE_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_REMOTE_HPP__

#include <PxPhysicsAPI.h>

#include <Nebula/Actor/Remote.hh>
#include <Nebula/Actor/Actor/Base.hh>

namespace Neb {
	namespace Actor {
		namespace Actor {
			class Remote:
				virtual public Neb::Actor::Actor::Base,
				virtual public Neb::Actor::Remote
			{
				public:
					template<class D, typename... Args> inline void		dispatch(Args... a) {
						Neb::Actor::Remote::dispatch<D>(a...);
						Neb::Actor::Actor::Base::dispatch<D>(a...);
						D::visit(this, a...);
					}

					virtual void		step(double dt);
			};
		}
	}
}

#endif


