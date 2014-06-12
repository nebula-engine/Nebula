#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_EMPTY_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_EMPTY_HPP__

#include <memory>


//#include <tinyxml/tinyxml.h>

//#include <math/transform.hpp>

#include <Nebula/Core/TimeStep.hpp>

#include <Nebula/Actor/Base.hh>
#include <Nebula/Actor/Util/Types.hh>

namespace neb { namespace core { namespace actor {
namespace neb {
	namespace Actor {
		class Empty: public Neb::Actor::Base {
			public:
				Empty(Neb::Actor::Util::Parent_s);
				virtual void			init();
				virtual void			release();
				virtual void			step(Neb::Core::TimeStep const & ts);
		};
	}
}


#endif


