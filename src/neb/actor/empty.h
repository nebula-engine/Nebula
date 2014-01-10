#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_EMPTY_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_EMPTY_HPP__

#include <memory>


//#include <tinyxml/tinyxml.h>

#include <math/transform.h>

#include <glutpp/actor/actor.h>

#include <PxPhysicsAPI.h>

#include <neb/actor/Base.h>
#include <glutpp/actor/desc.h>

namespace neb
{
	namespace actor
	{
		class empty: public neb::actor::Base
		{
			public:
				empty(
						neb::scene::scene_shared,
						neb::actor::Base_shared = neb::actor::Base_shared());
				
				virtual void			init(glutpp::actor::desc_shared);

				virtual void			create_physics(std::shared_ptr<neb::shape>);
				
				virtual void			create_physics();
				virtual void			init_physics();
				
				virtual void			add_force() {}

		};
	}
}


#endif








