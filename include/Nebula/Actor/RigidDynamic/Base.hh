#ifndef NEBULA_ACTOR_RIGID_DYNAMIC_BASE_HH
#define NEBULA_ACTOR_RIGID_DYNAMIC_BASE_HH

#include <Nebula/Actor/RigidBody/Base.hh>

namespace neb { namespace core { namespace actor {
		

namespace rigiddynamic {
			class Base: public neb::core::actor::rigidbody::Base {
				public:
					Base();
					Base(sp::shared_ptr<neb::core::actor::Util::Parent>);

					virtual void				init();

			};
		}
	}
}}


#endif








