#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_STATIC_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_STATIC_HPP__

#include <neb/actor/Rigid_Actor.h>

namespace neb
{
	namespace actor
	{
		class Rigid_Static:
			public neb::actor::Rigid_Actor
		{
		public:
			virtual void	init();
			virtual void	add_force();
		};
	}
}

#endif


