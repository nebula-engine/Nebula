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

					template<class D, typename... Args> inline void	dispatch(Args... a) {
						D::visit(this, a...);
					}
					
					virtual void				init();

					virtual Neb::Actor::Base_s		get_projective();

					virtual void				create_physics();
					virtual void				init_physics();
			};
		}
	}
}


#endif








