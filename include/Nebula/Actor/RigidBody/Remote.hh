#ifndef NEBULA_CONTENT_ACTOR_RIGID_BODY_REMOTE_HH
#define NEBULA_CONTENT_ACTOR_RIGID_BODY_REMOTE_HH

#include <Nebula/Actor/RigidActor/Remote.hh>
#include <Nebula/Actor/RigidBody/Base.hh>

namespace neb { namespace core { namespace actor {
		

namespace RigidBody {
			class Remote:
				virtual public neb::core::actor::RigidBody::Base,
				virtual public neb::core::actor::RigidActor::Remote
			{
				public:
					virtual void		step(neb::core::TimeStep const & ts);
			};


		}
}	}
}

#endif


