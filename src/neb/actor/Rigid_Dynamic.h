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
						glutpp::actor::desc_shared,
						std::shared_ptr<neb::scene::scene>,
						neb::actor::Base_shared = neb::actor::Base_shared());
				
				virtual void		init();


				virtual void			create_physics();
				virtual void			init_physics();
		};
	}
}

#endif








