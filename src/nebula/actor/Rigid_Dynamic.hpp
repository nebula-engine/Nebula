#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_DYNAMIC_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_RIGID_DYNAMIC_HPP__

#include <neb/actor/rigid_body/rigid_body.h>

namespace neb
{
	namespace actor
	{
		class Rigid_Dynamic: public neb::actor::rigid_body::rigid_body
		{
			public:
				Rigid_Dynamic(glutpp::parent_s);
				
				virtual void		init(glutpp::actor::desc_s);

				virtual void		create_physics();
				virtual void		init_physics();

				virtual void		print_info();
		};
	}
}

#endif








