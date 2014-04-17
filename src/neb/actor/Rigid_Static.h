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
				Rigid_Static(glutpp::parent_s parent);

				virtual void	init(glutpp::actor::desc_s);

				virtual void	create_physics();
				virtual void	init_physics();
				
				virtual void	step_local(double);
				virtual void	step_remote(double);
		};
	}
}

#endif


