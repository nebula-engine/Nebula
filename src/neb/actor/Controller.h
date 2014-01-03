#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_CONTROLLER_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_CONTROLLER_HPP__

#include <PxPhysicsAPI.h>

#include <neb/actor/Base.h>

namespace neb
{
	namespace actor
	{
		class Controller:
			public neb::actor::Base
		{
			public:
				Controller(
						glutpp::actor::desc*,
						std::shared_ptr<neb::scene::scene>);
				virtual void		release();

				virtual void		step(float);
				virtual void		init();
				virtual void		add_force();


				physx::PxController*	px_controller_;

		};
	}
}



#endif

