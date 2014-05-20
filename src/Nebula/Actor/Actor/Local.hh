#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_LOCAL_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_ACTOR_LOCAL_HPP__

#include <PxPhysicsAPI.h>

#include <Nebula/Actor/Local.hh>
#include <Nebula/Actor/Actor/Base.hh>

namespace Neb {
	namespace Actor {
		namespace Actor {
			class Local:
				virtual public Neb::Actor::Actor::Base,
				virtual public Neb::Actor::Local
			{
				public:
					template<class D, typename... Args> inline void		dispatch(Args... a) {
						Neb::Actor::Local::dispatch<D>(a...);
						Neb::Actor::Actor::Base::dispatch<D>(a...);
						D::visit(this, a...);
					}

					virtual void		step(double const & time, double const & dt);
			};
		}
	}
}

#endif


