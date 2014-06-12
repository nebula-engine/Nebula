#ifndef NEBULA_ACTOR_UTIL_CAST_HH
#define NEBULA_ACTOR_UTIL_CAST_HH

#include <Galaxy-Standard/shared.hpp>

#include <Nebula/Actor/Util/Types.hh>

namespace neb {
        namespace Actor {
                namespace Util {
                        class Cast: virtual public gal::std::shared {
				public:
					sp::shared_ptr<neb::Actor::Base>				isActorBase();
					sp::shared_ptr<neb::Actor::Actor::Base>				isActorActor();
					sp::shared_ptr<neb::Actor::RigidActor::Base>			isActorRigidActor();
					sp::shared_ptr<neb::Actor::RigidBody::Base>			isActorRigidBody();
			};
		}
	}
}

#endif
