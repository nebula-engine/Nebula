#ifndef NEBULA_ACTOR_RIGID_DYNAMIC_BASE_HH
#define NEBULA_ACTOR_RIGID_DYNAMIC_BASE_HH

#include <Nebula/Actor/RigidBody/Base.hh>

namespace Neb {
	namespace Actor {
		namespace RigidDynamic {
			class Base: public Neb::Actor::RigidBody::Base {
				public:
					Base();
					Base(Neb::Actor::Util::Parent_s);

					virtual void		init();

					virtual void		create_physics();
					virtual void		init_physics();
			};
		}
	}
}


#endif








