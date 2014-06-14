#ifndef NEBULA_ACTOR_RIGID_DYNAMIC_LOCAL_HH
#define NEBULA_ACTOR_RIGID_DYNAMIC_LOCAL_HH

#include <Nebula/Actor/RigidDynamic/Base.hh>
#include <Nebula/Actor/RigidBody/Local.hh>

namespace neb { namespace core { namespace actor {
		

namespace rigiddynamic {
			class local:
				virtual public neb::core::actor::RigidBody::local,
				virtual public neb::core::actor::rigiddynamic::Base
			{
				public:
					local(sp::shared_ptr<neb::core::actor::Util::Parent> parent);

					virtual void				init();
					virtual void				release();
					virtual void				step(neb::core::TimeStep const & ts);
			};


}		}
	}
}

#endif


