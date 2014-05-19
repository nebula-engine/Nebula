#ifndef NEBULA_ACTOR_RIGID_DYNAMIC_LOCAL_HH
#define NEBULA_ACTOR_RIGID_DYNAMIC_LOCAL_HH

#include <Nebula/Actor/RigidDynamic/Base.hh>
#include <Nebula/Actor/RigidBody/Local.hh>

namespace Neb {
	namespace Actor {
		namespace RigidDynamic {
			class Local:
				virtual public Neb::Actor::RigidDynamic::Base,
				virtual public Neb::Actor::RigidBody::Local
			{

				public:
					Local();
					Local(Neb::Actor::Util::Parent_w);

					virtual void		init();

					virtual void		step(double dt);

					virtual void		create_physics();
					virtual void		init_physics();
			};
		}
	}
}

#endif


