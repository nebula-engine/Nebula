#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_LOCAL_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_ACTOR_LOCAL_HPP__

#include <Nebula/core/actor/Actor/Local.hh>
#include <Nebula/core/actor/RigidActor/Base.hh>

namespace neb { namespace core { namespace actor {
		

namespace rigidactor {
			class local:
				virtual public neb::core::actor::rigidactor::base,
				virtual public neb::core::actor::actor::local
			{
				public:
					local(sp::shared_ptr<neb::core::actor::util::parent> parent);

					virtual void				step(neb::core::TimeStep const & ts);
			};


}		}
}
}

#endif








