#ifndef NEBULA_CONTENT_ACTOR_RIGID_BODY_LOCAL_HH
#define NEBULA_CONTENT_ACTOR_RIGID_BODY_LOCAL_HH

#include <Nebula/Actor/Util/Types.hh>

#include <Nebula/Actor/RigidActor/Local.hh>
#include <Nebula/Actor/RigidBody/Base.hh>

namespace Neb {
	namespace Actor {
		namespace RigidBody {
			class Local:
				virtual public Neb::Actor::RigidActor::Local,
				virtual public Neb::Actor::RigidBody::Base
			{
				public:
					virtual void		step(Neb::Core::TimeStep const & ts);
	
					virtual Neb::Actor::Base_s		get_projective();
			};
		}
	}
}

#endif


