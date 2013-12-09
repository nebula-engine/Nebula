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
				Controller();


				virtual void	step( float );
				virtual void	Display();



				physx::PxController*                                    px_controller_;

		};
	}
}



#endif

