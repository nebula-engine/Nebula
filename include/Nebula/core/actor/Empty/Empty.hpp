#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_EMPTY_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_EMPTY_HPP__

#include <memory>


//#include <tinyxml/tinyxml.h>

//#include <math/transform.hpp>

#include <Nebula/core/TimeStep.hpp>

#include <Nebula/core/actor/Base.hh>
#include <Nebula/core/actor/Util/Types.hh>

namespace neb { namespace core { namespace actor {


	class Empty: public neb::core::actor::base {
		public:
			Empty(sp::shared_ptr<neb::core::actor::util::parent>);
			virtual void			init();
			virtual void			release() {}
			virtual void			step(neb::core::TimeStep const & ts) {}
	};
}


}}


#endif


