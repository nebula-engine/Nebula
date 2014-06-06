#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_LOCAL_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_LOCAL_HPP__

#include <Nebula/Actor/Actor/Local.hh>
#include <Nebula/Actor/RigidActor/Base.hh>

namespace Neb {
	namespace Actor {
		namespace RigidActor {
			class Local:
				virtual public Neb::Actor::RigidActor::Base,
				virtual public Neb::Actor::Actor::Local
			{
				public:
					virtual void				step(Neb::Core::TimeStep const & ts);

					virtual Neb::Actor::Base_s		get_projective();
			};
		}
	}
}

#endif








