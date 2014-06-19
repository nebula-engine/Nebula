#ifndef NEBULA_CONTENT_ACTOR_RIGID_BODY_REMOTE_HH
#define NEBULA_CONTENT_ACTOR_RIGID_BODY_REMOTE_HH

#include <Nebula/Actor/RigidActor/Remote.hh>
#include <Nebula/Actor/RigidBody/Base.hh>

namespace neb { namespace core { namespace actor {
		

namespace rigidbody {
			class remote:
				virtual public neb::core::actor::rigidbody::base,
				virtual public neb::core::actor::rigidactor::remote
			{
				public:
					virtual void		step(neb::core::TimeStep const & ts);
			};


		}
}	}
}

#endif


