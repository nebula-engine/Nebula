#ifndef NEBULA_ACTOR_RIGID_DYNAMIC_LOCAL_HH
#define NEBULA_ACTOR_RIGID_DYNAMIC_LOCAL_HH

#include <Nebula/Actor/RigidDynamic/Base.hh>
#include <Nebula/Actor/RigidBody/Local.hh>

namespace neb { namespace core { namespace actor {
		

namespace RigidDynamic {
			class Local:
				virtual public neb::core::actor::RigidBody::Local,
				virtual public neb::core::actor::RigidDynamic::Base
			{
				public:
					Local();
					Local(sp::shared_ptr<neb::core::actor::Util::Parent> parent);

					virtual void				init();
					virtual void				release();
					virtual void				step(neb::core::TimeStep const & ts);
			};


}		}
	}
}

#endif


