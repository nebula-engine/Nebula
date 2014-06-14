#ifndef NEBULA_ACTOR_UTIL_CAST_HH
#define NEBULA_ACTOR_UTIL_CAST_HH

#include <Galaxy-Standard/shared.hpp>

#include <Nebula/Actor/Util/Types.hh>

namespace neb { namespace core {
        namespace actor {
                namespace Util {
                        class Cast: virtual public gal::std::shared {
				public:
					sp::shared_ptr<neb::core::actor::Base>				isActorBase();
					sp::shared_ptr<neb::core::actor::actor::Base>				isActorActor();
					sp::shared_ptr<neb::core::actor::rigidactor::Base>			isActorRigidActor();
					sp::shared_ptr<neb::core::actor::rigidbody::Base>			isActorRigidBody();
			};
		}
	}
}}

#endif
