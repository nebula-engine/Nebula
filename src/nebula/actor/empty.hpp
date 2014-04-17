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
				empty(glutpp::parent_s);
				
				virtual void			init(glutpp::actor::desc_s);

				virtual void			create_physics(std::shared_ptr<neb::shape>);
				
				virtual void			create_physics();
				virtual void			init_physics();
				
				virtual void			add_force(double) {}

		};
	}
}


#endif


