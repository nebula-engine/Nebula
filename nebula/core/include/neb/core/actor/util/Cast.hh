#ifndef NEBULA_ACTOR_UTIL_CAST_HH
#define NEBULA_ACTOR_UTIL_CAST_HH

#include <Galaxy-Standard/shared.hpp>

#include <neb/core/actor/Util/Types.hh>

namespace neb { namespace core { namespace actor { namespace util {



                        class cast: virtual public gal::std::shared {
				public:
					sp::shared_ptr<neb::core::actor::base>				isActorBase();
					sp::shared_ptr<neb::core::actor::actor::base>				isActorActor();
					sp::shared_ptr<neb::core::actor::rigidactor::base>			isActorRigidActor();
					sp::shared_ptr<neb::core::actor::rigidbody::base>			isActorRigidBody();
			};


}}}}

#endif
