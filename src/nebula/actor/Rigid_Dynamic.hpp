#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_DYNAMIC_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_DYNAMIC_HPP__

#include <nebula/actor/rigid_body/rigid_body.hpp>

namespace neb {
	namespace Actor {
		class Rigid_Dynamic:
			public neb::Actor::RigidBody::RigidBody
		{
			public:
				Rigid_Dynamic(boost::shared_ptr<glutpp::actor::parent>);
				
				virtual void		init(boost::shared_ptr<glutpp::actor::desc>);

				virtual void		create_physics();
				virtual void		init_physics();

				virtual void		print_info();
		};
	}
}

#endif








