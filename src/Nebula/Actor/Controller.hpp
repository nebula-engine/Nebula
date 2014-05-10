#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_CONTROLLER_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_CONTROLLER_HPP__

#include <PxPhysicsAPI.h>

#include <Nebula/Actor/Base.hpp>

namespace Neb {
	namespace Actor {
		class Controller: public Neb::Actor::Base {
			public:
				Controller(Neb::Actor::parent_w);
				
				virtual void		release();

				virtual void		step(float);
				//virtual void		init(Neb::Actor::desc_w);
				virtual void		add_force();


				physx::PxController*	px_controller_;

		};
	}
}



#endif

