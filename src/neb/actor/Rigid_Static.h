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
				Rigid_Static(
						glutpp::actor::desc*,
						std::shared_ptr<neb::scene::scene>,
						neb::actor::Base_shared = neb::actor::Base_shared());

				virtual void	init();
				virtual void	create_physics();
				virtual void	init_physics();
				
				virtual void	add_force();
		};
	}
}

#endif


