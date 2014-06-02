#ifndef NEBULA_ACTOR_UTIL_CAST_HH
#define NEBULA_ACTOR_UTIL_CAST_HH

#include <Galaxy-Standard/shared.hpp>

#include <Nebula/Actor/Util/Types.hh>

namespace Neb {
        namespace Actor {
                namespace Util {
                        class Cast: virtual public gal::std::shared {
				public:
					sp::shared_ptr<Neb::Actor::Base>				isActorBase();
					sp::shared_ptr<Neb::Actor::Actor::Base>				isActorActor();
					sp::shared_ptr<Neb::Actor::RigidActor::Base>			isActorRigidActor();
					sp::shared_ptr<Neb::Actor::RigidBody::Base>			isActorRigidBody();
			};
		}
	}
}

#endif
