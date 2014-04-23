#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_EMPTY_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_EMPTY_HPP__

#include <memory>


//#include <tinyxml/tinyxml.h>

#include <math/transform.hpp>


#include <PxPhysicsAPI.h>

#include <nebula/actor/Base.hpp>

#include <gru/actor/desc.hpp>
#include <gru/actor/actor.hpp>

namespace neb {
	namespace Actor {
		class empty: public neb::Actor::Base {
			public:
				empty(glutpp::actor::parent_s);
				
				virtual void			init(glutpp::actor::desc_s);

				virtual void			add_force(double) {}

				virtual void			create_physics() {};
				virtual void			init_physics() {};
		};
	}
}


#endif


