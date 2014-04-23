#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_CONTROLLER_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_CONTROLLER_HPP__

#include <PxPhysicsAPI.h>

#include <nebula/actor/Base.hpp>

namespace neb {
	namespace Actor {
		class Controller:
			public neb::Actor::Base
		{
			public:
				Controller(glutpp::actor::parent_s);
				
				virtual void		release();

				virtual void		step(float);
				virtual void		init(glutpp::actor::desc_s);
				virtual void		add_force();


				physx::PxController*	px_controller_;

		};
	}
}



#endif

