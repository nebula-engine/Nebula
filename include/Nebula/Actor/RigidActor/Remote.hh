#ifndef NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_REMOTE_HH
#define NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_REMOTE_HH

#include <Nebula/Actor/Actor/Remote.hh>
#include <Nebula/Actor/RigidActor/Base.hh>

namespace neb { namespace core { namespace actor {
namespace neb {
	namespace Actor {
		namespace RigidActor {
			class Remote:
				virtual public neb::Actor::RigidActor::Base,
				virtual public neb::Actor::Actor::Remote
			{
				public:
					virtual void		step(neb::core::TimeStep const & ts);
			};
		}
	}
}

#endif





