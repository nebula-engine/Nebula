#ifndef NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_REMOTE_HH
#define NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_REMOTE_HH

#include <Nebula/Actor/Actor/Remote.hh>
#include <Nebula/Actor/RigidActor/Base.hh>

namespace Neb {
	namespace Actor {
		namespace RigidActor {
			class Remote:
				virtual public Neb::Actor::RigidActor::Base,
				virtual public Neb::Actor::Actor::Remote
			{
				public:
					virtual void		step(double const & time, double const & dt);
			};
		}
	}
}

#endif





