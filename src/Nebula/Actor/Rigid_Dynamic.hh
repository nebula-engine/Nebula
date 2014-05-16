#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_DYNAMIC_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_DYNAMIC_HPP__

#include <Nebula/Actor/rigid_body/rigid_body.hh>

namespace Neb {
	namespace Actor {
		class Rigid_Dynamic: public Neb::Actor::RigidBody::Base {
			public:
				Rigid_Dynamic(Neb::Actor::Util::Parent_w);
				
				virtual void		init();

				virtual void		create_physics();
				virtual void		init_physics();

				virtual void		print_info();
		};
	}
}

#endif








