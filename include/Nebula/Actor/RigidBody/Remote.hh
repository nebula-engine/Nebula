#ifndef NEBULA_CONTENT_ACTOR_RIGID_BODY_REMOTE_HH
#define NEBULA_CONTENT_ACTOR_RIGID_BODY_REMOTE_HH

#include <Nebula/Actor/RigidActor/Remote.hh>
#include <Nebula/Actor/RigidBody/Base.hh>

namespace neb { namespace core { namespace actor {
		

namespace rigidbody {
			class Remote:
				virtual public neb::core::actor::rigidbody::Base,
				virtual public neb::core::actor::rigidactor::Remote
			{
				public:
					virtual void		step(neb::core::TimeStep const & ts);
			};


		}
}	}
}

#endif


