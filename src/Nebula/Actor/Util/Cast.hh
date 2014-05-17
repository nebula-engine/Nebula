#ifndef NEBULA_ACTOR_UTIL_CAST_HH
#define NEBULA_ACTOR_UTIL_CAST_HH

#include <Nebula/Util/Shared.hh>

#include <Nebula/Actor/Util/Types.hh>

namespace Neb {
        namespace Actor {
                namespace Util {
                        class Cast:
				virtual public Neb::Util::Shared
			{
                                public:
                                        Neb::Actor::Base_s				isActorBase();
        				Neb::Actor::Actor::Base_s			isActorActor();
        				Neb::Actor::RigidActor::Base_s			isActorRigidActor();
        				Neb::Actor::RigidBody::Base_s			isActorRigidBody();
                        };
                }
        }
}

#endif
