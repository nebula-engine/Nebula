#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_CONTROLLER_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_CONTROLLER_HPP__

#include <PxPhysicsAPI.h>

#include <NEB/Actor/Base.h>

namespace NEB
{
	namespace Actor
	{
		class Controller:
			public NEB::Actor::Base
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

