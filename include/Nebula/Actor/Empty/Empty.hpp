#ifndef __NEBULA_CONTENT_ACTOR_PHYSICS_EMPTY_HPP__
#define __NEBULA_CONTENT_ACTOR_PHYSICS_EMPTY_HPP__

#include <memory>


//#include <tinyxml/tinyxml.h>

//#include <math/transform.hpp>

#include <Nebula/Core/TimeStep.hpp>

#include <Nebula/Actor/Base.hh>
#include <Nebula/Actor/Util/Types.hh>

namespace neb { namespace core { namespace actor {


	class Empty: public neb::core::actor::Base {
		public:
			Empty(sp::shared_ptr<neb::core::actor::Util::Parent>);
			virtual void			init();
			virtual void			release();
			virtual void			step(neb::core::TimeStep const & ts);
	};
}


}}


#endif


