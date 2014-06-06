#ifndef NEBULA_ACTOR_RIGID_DYNAMIC_LOCAL_HH
#define NEBULA_ACTOR_RIGID_DYNAMIC_LOCAL_HH

#include <Nebula/Actor/RigidDynamic/Base.hh>
#include <Nebula/Actor/RigidBody/Local.hh>

namespace Neb {
	namespace Actor {
		namespace RigidDynamic {
			class Local:
				virtual public Neb::Actor::RigidBody::Local,
				virtual public Neb::Actor::RigidDynamic::Base
			{
				public:
					Local();
					Local(Neb::Actor::Util::Parent_s);

					virtual void				init();

					virtual void				step(Neb::Core::TimeStep const & ts);

					virtual Neb::Actor::Base_s		get_projectile();
					
					virtual void				add_force(double);

					virtual void				create_physics();
					virtual void				init_physics();
			};
		}
	}
}

#endif


