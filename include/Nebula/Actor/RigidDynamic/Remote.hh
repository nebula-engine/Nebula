#ifndef NEBULA_ACTOR_RIGID_DYNAMIC_REMOTE_HH
#define NEBULA_ACTOR_RIGID_DYNAMIC_REMOTE_HH

#include <Nebula/Actor/RigidBody/Remote.hh>
#include <Nebula/Actor/RigidDynamic/Base.hh>

namespace neb {
	namespace Actor {
		namespace RigidDynamic {
			class Remote:
				virtual public Neb::Actor::RigidBody::Remote,
				virtual public Neb::Actor::RigidDynamic::Base
			{
				public:
					Remote();
					Remote(Neb::Actor::Util::Parent_w);

					virtual void		create_physics();
					virtual void		init_physics();
			};
		}
	}
}

#endif


