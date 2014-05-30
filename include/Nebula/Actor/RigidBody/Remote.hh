#ifndef NEBULA_CONTENT_ACTOR_RIGID_BODY_REMOTE_HH
#define NEBULA_CONTENT_ACTOR_RIGID_BODY_REMOTE_HH

#include <Nebula/Actor/RigidActor/Remote.hh>
#include <Nebula/Actor/RigidBody/Base.hh>

namespace Neb {
	namespace Actor {
		namespace RigidBody {
			class Remote:
				virtual public Neb::Actor::RigidBody::Base,
				virtual public Neb::Actor::RigidActor::Remote
			{
				public:
					template<class D, typename... Args> inline void		dispatch(Args... a) {
						Neb::Actor::RigidActor::Remote::dispatch<D>(a...);
						Neb::Actor::RigidBody::Base::dispatch<D>(a...);
						D::visit(this, a...);
					}

					virtual void		step(double const & time, double const & dt);
				
			};
		}
	}
}

#endif


