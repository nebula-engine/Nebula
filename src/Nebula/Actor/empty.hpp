#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_EMPTY_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_EMPTY_HPP__

#include <memory>


//#include <tinyxml/tinyxml.h>

//#include <math/transform.hpp>


#include <PxPhysicsAPI.h>

#include <Nebula/Actor/Base.hpp>
#include <Nebula/Actor/Types.hpp>
#include <Nebula/Actor/Util/desc.hpp>

namespace Neb {
	namespace Actor {
		class empty: public Neb::Actor::Base {
			public:
				empty(Neb::Actor::parent_w);
				
				virtual void			init(Neb::Actor::desc_w);

				virtual void			add_force(double) {}

				virtual void			create_physics() {};
				virtual void			init_physics() {};
		};
	}
}


#endif


