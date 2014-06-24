#ifndef NEBULA_ACTOR_RIGID_DYNAMIC_BASE_HH
#define NEBULA_ACTOR_RIGID_DYNAMIC_BASE_HH

#include <Nebula/core/actor/RigidBody/Base.hh>

namespace neb { namespace core { namespace actor {
		

namespace rigiddynamic {
			class base:
				virtual public neb::core::actor::rigidbody::base
			{
				public:
					base(sp::shared_ptr<neb::core::actor::util::parent> parent);

					virtual void				init();
					virtual void				release() = 0;
					//virtual void				releaseUp();
					
			};
		}
	}
}}


#endif








