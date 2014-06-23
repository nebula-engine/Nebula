#ifndef NEBULA_ACTOR_RIGID_DYNAMIC_LOCAL_HH
#define NEBULA_ACTOR_RIGID_DYNAMIC_LOCAL_HH

#include <Nebula/core/actor/RigidDynamic/Base.hh>
#include <Nebula/core/actor/RigidBody/Local.hh>

namespace neb { namespace core { namespace actor {
		

namespace rigiddynamic {
			class local:
				virtual public neb::core::actor::rigidbody::local,
				virtual public neb::core::actor::rigiddynamic::base
			{
				public:
					local(sp::shared_ptr<neb::core::actor::util::parent> parent);

					virtual void				init();
					virtual void				release();
					virtual void				step(gal::std::timestep const & ts);
			};


}		}
	}
}

#endif


