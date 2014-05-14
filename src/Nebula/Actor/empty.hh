#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_EMPTY_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_EMPTY_HPP__

#include <memory>


//#include <tinyxml/tinyxml.h>

//#include <math/transform.hpp>


#include <PxPhysicsAPI.h>

#include <Nebula/Actor/Base.hh>
#include <Nebula/Actor/Util/Types.hh>

namespace Neb {
	namespace Actor {
		class empty: public Neb::Actor::Base {
			public:
				empty(Neb::Actor::Util::Parent_s);
				
				virtual void			init();

				virtual void			add_force(double) {}

				virtual void			create_physics() {};
				virtual void			init_physics() {};
		};
	}
}


#endif


