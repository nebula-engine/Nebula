#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_DYNAMIC_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_DYNAMIC_HPP__

#include <neb/actor/Rigid_Body.h>

namespace neb
{
	namespace actor
	{
		class Rigid_Dynamic: public neb::actor::Rigid_Body
		{
			public:
				Rigid_Dynamic(
						neb::scene::scene_s,
						neb::actor::Base_s = neb::actor::Base_s());
				
				virtual void		init(glutpp::actor::desc_s);

				virtual void		create_physics();
				virtual void		init_physics();
		};
	}
}

#endif








